/*
 * FILE: conn.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: create connection with remote server
 */

#ifndef CONN_H
#define CONN_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

typedef struct conn_s {
    int sock;
    url_t url_info;
    int avaliable;
} conn_t;

conn_t build_conn(const char* url);

#endif
