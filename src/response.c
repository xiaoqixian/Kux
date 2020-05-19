/*
 * FILE: download.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 */

#include "download.h"

int parse_response(conn_t conn, const char* file_url, response_t* resp) {
    if (!conn.avaliable) {
        LOG_ERR("connection unavaliable");
        return -1;
    }
    
    char buffer[MAX_BUFFER_SIZE] = {0};
    char* i = NULL;
    //char* location_start;

    ssize_t size = recv(conn.sock, buffer, sizeof(buffer), 0);
    ASSERT(size > 0, "recv nothing");
    DEBUG("recv in buffer: %s", buffer);
    
    if (strstr(buffer, "HTTP/1.1 404") != NULL || strstr(buffer, "HTTP/1.1 404") != NULL) {
        LOG_INFO("404 status code from the website");
        return -1;
    }
    
    //the redirect function will be added later.
    //location_start = (char*)strstr(buffer, "Location:");
    
    //parse file size
    i = strstr(buffer, "Content-Length:");
    if (i == NULL) {
        LOG_ERR("file size unknown");
    }
    
    sscanf(i, "Content-Length: %lu", &resp->file_size);
    DEBUG("response Content-Length: %lu\n", resp->file_size);
    LOG_INFO("file size: %lu", resp->file_size);

    //parse file name
    i = NULL;
    i = strrchr(file_url, '/');
    if (i == NULL) {
        strcpy(resp->file_name, file_url);
    }
    else {
        strcpy(resp->file_name, ++i);
    }
    DEBUG("file name: %s", resp->file_name);
    close(conn.sock);
    return 0;
}


