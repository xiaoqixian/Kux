/*
 * FILE: parse.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: parse http url
 */

#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "debug.h"

typedef struct url_s {
    char scheme[8];
    char host[256];
    char host_name[256];
    unsigned int port;
    char file[256];
} url_t;

url_t parse_url(const char* url);

#endif
