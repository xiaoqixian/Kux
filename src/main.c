/*
 * FILE: main.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: main function
 */

#include "debug.h"
#include "parse.h"
#include "conn.h"
#include "request.h"
#include "download.h"

int main(int argc, char* argv[]) {
    conn_t conn = build_conn(argv[1]);
    send_request(conn);
    parse_response(conn, conn.url_info.file);
    return 0;
}
