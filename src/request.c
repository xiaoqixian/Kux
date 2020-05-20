/*
 * FILE: request.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 */

#include <stdio.h>
#include <string.h>
#include "request.h"

int send_request(conn_t conn) {
    if (!conn.avaliable) {
        LOG_ERR("conn is unavaliable");
        return -1;
    }
    char req[MAX_REQ_SIZE] = {0};

    sprintf(req, "GET %s HTTP/1.1\nHost: %s\nAccept: */*\nReferer: http://%s\nUser-Agent: Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)\nPragma: no-cache\nCache-Control: no-cache\nConnection: close\n\n", conn.url_info.file, conn.url_info.host_name, conn.url_info.host_name);
    
    ssize_t size = send(conn.sock, req, strlen(req), 0);
    if (size != strlen(req)) {
        LOG_ERR("send error");
        return -1;
    }
    DEBUG("send request successfully");
    return 0;
}

int send_request_range(conn_t conn, thread_info_t* info) {
    if (!conn.avaliable) {
        LOG_ERR("conn is unavaliable");
        return -1;
    }
    char req[MAX_REQ_SIZE] = {0};

    sprintf(req, "GET %s HTTP/1.1\nHost: %s\nAccept: */*\nReferer: http://%s\nUser-Agent: Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)\nRange: bytes=%d-%d\nPragma: no-cache\nCache-Control: no-cache\n\n", conn.url_info.file, conn.url_info.host_name, conn.url_info.host_name, info->start, (int)(info->start + info->limit-1));
    
    ssize_t size = send(conn.sock, req, strlen(req), 0);
    if (size != strlen(req)) {
        LOG_ERR("send error");
        return -1;
    }
    DEBUG("send request successfully");
    return 0;
}


