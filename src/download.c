/*
 * 
 */

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "response.h"
#include "conn.h"
#include "request.h"

void* download_range(void* arg) {
    DEBUG("running download range");
    thread_info_t* thread_info = (thread_info_t*)arg;
    char buffer[MAX_RECV_SIZE] = {0};
    ssize_t size, write_size;
    size_t downloaded = 0;
    char* body = NULL;
    
    conn_t conn = build_conn(thread_info->url);
    if (!conn.avaliable) {
        LOG_ERR("thread %d build connection failed\n", thread_info->num);
        return NULL;
    }
    
send_again:
    ASSERT(send_request_range(conn, thread_info) != -1, "send request range error");
    DEBUG("send request range");
    
    size = recv(conn.sock, buffer, sizeof(buffer), 0);
    DEBUG("download recv size:%zd", size);
    
    if (strstr(buffer, "HTTP/1.1 206") == NULL && strstr(buffer, "HTTP/1.0 206") == NULL && strstr(buffer, "HTTP/1.1 200") == NULL && strstr(buffer, "HTTP/1.0 200") == NULL) {
        sleep(2);
        memset(buffer, 0, sizeof(buffer));
        conn = build_conn(thread_info->url);
        goto send_again;
    }
    DEBUG("recv buffer: %s\n", buffer);
    
    body = strstr(buffer, "\r\n\r\n") + 4;
    if (body != NULL) {
        size -= (body - buffer);
        fseek(thread_info->fw, thread_info->start, SEEK_SET);
        write_size = fwrite(body, sizeof(char), size, thread_info->fw);
        ASSERT(write_size == size, "fwrite error");
        fflush(thread_info->fw);
        downloaded += size;
        
        while (downloaded < thread_info->limit) {
            memset(buffer, 0, sizeof(buffer));
            size = recv(conn.sock, buffer, sizeof(buffer), 0);
            if (size == 0) {
                conn.avaliable = 0;
                while (!conn.avaliable) {
                    sleep(2);
                    conn = build_conn(thread_info->url);
                }
                thread_info->start += downloaded;
                goto send_again;
            }
            
            write_size = fwrite(buffer, sizeof(char), size, thread_info->fw);
            ASSERT(write_size == size, "fwrite error");
            fflush(thread_info->fw);
            downloaded += size;
        }
        fclose(thread_info->fw);
        close(conn.sock);
    }
    pthread_exit(NULL);
}

void info_free(thread_info_t** infos, const int thread_num) {
    int i;
    for (i = 0; i < thread_num; i++) {
        free(infos[i]);
    }
}
