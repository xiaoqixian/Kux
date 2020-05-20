/*
 * FILE: request.h
 * Copyrgiht (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: build a request and send it to the remote server to get
 * resource.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include "download.h"
#include "conn.h"

#define MAX_REQ_SIZE 1024

int send_request(conn_t conn);

int send_request_range(conn_t conn, thread_info_t* info);

#endif
