/*
 * FILE: response.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: receive http response and download files.
 */

#ifndef RESPONSE_H
#define RESPONSE_H

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "debug.h"
#include "conn.h"

#define MAX_BUFFER_SIZE 1024
#define MAX_NAME_SIZE 256

typedef struct response_s {
    char file_name[MAX_NAME_SIZE];
    unsigned long file_size; //the length of unsigned long decides the maximum size to receive, which is about 4295MB.
} response_t;

int parse_response(conn_t conn, const char* file_url, response_t* resp);

#endif
