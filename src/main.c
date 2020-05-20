/*
 * FILE: main.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: main function
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <getopt.h>
#include "debug.h"
#include "parse.h"
#include "conn.h"
#include "request.h"
#include "download.h"
#include "response.h"

#define KUX_VERSION "1.0"
#define PROJECT_NAME "KUX"

//globals
static int thread_num = 5;

static const struct option long_options[] = {
    {"help", no_argument, NULL, '?'},
    {"threads", optional_argument, NULL, 't'},
    {"port", optional_argument, NULL, 'p'},
    {"path", optional_argument, NULL, 'w'},
    {"resource", required_argument, NULL, 'r'}
};

static void usage() {
    fprintf(stderr,
            "Kux [options]\n"
            "   -h|--help This information\n"
            "   -t|--threads specify threads number, optional, default 5, maximum 20\n"
            "   -p|--port specify the local port, optional, default 9090\n"
            "   -w|--path specify the file storage path, optioal, default current path\n"
            "   -r|--resource resource url, required\n"
           );
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        usage();
        return 0;
    }
    
    int res, opt = 0;
    int option_index = 0;
    char* url = NULL;
    int port = 9090;
    char* path = ".";
    response_t resp = {0};
    FILE* fw = NULL;
    pthread_mutex_t mutex_lock;
    thread_info_t* infos[thread_num];
    pthread_t threads[thread_num];
    unsigned long chunk_size = 0;
    
    printf("-----Thanks For Using Kux-----\n");
    //figure
    
    while ((opt = getopt_long(argc, argv, "?t::p::w::r:", long_options,&option_index)) != EOF) {
        switch (opt) {
            case '0':
                break;
            case '?':
            case 'h':
            case ':':
                usage();
                return 0;
            case 't':
                sscanf(optarg, "%d", &thread_num);
                DEBUG("thread num:%d\n", thread_num);
                break;
            case 'p':
                sscanf(optarg, "%d", &port);
                if (port > 65535) {
                    LOG_ERR("port is bigger than maximum port, automatically swtiched to 9090 port");
                    port = 9090;
                }
                break;
            case 'w':
                path = optarg;
                break;
            case 'r':
                url = optarg;
                break;
        }
    }
    if (url == NULL) {
        fprintf(stderr, "please input the resource url\n");
        return -1;
    }
   
    conn_t conn = build_conn(url);
    if (!conn.avaliable) {
        LOG_ERR("build connection error");
    }

    res = send_request(conn);
    ASSERT(res == 0, "send request error");
    
    url_t url_info = parse_url(url);
    res = parse_response(conn, url_info.file, &resp);
    ASSERT(res == 0, "parse response error");
    chunk_size = resp.file_size/thread_num + 1;
    
    //strcat(path, resp.file_name);
    
    if ((fw = fopen(path, "wb")) == NULL) {
        LOG_ERR("directory not exits");
        return -1;
    }
    
    pthread_mutex_init(&mutex_lock, NULL);
    for (res = 0; res < thread_num; res++) {
        infos[res] = (thread_info_t*)malloc(sizeof(thread_info_t));
        memset(infos[res], 0, sizeof(thread_info_t));
        infos[res]->num = res;
        infos[res]->mutex_lock = &mutex_lock;
        infos[res]->fw = fw;
        infos[res]->url = url;
        infos[res]->start = res * chunk_size;
        if (res == thread_num - 1) {
            infos[res]->limit = resp.file_size - (thread_num - 1)*chunk_size;
        }
        else {
            infos[res]->limit = chunk_size;
        }
        
        pthread_create(&threads[res], NULL, download_range, (void*)infos[res]);
        LOG_INFO("thread %d start. start position:%d, limit:%lu", infos[res]->num, infos[res]->start, infos[res]->limit);
    }
    fclose(fw);
    pthread_mutex_destroy(&mutex_lock);
    info_free(infos, thread_num);
    LOG_INFO("download completes");

    return 0;
}
