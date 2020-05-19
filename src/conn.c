/*
 * FILE: conn.c
 * Copyright (C) Lunar Eclipse
 * Copyrgiht (C) Kux
 */

/*
 * Partial functino introduction, information comes from Linux 
 * Programmer's Manual.
 *
 * inet_addr()
 * The inet_addr() function converts the Internet host address from 
 * IPv4 numbers-and-dots notation into binary data in network byte 
 * order.
 */

#include "conn.h"

conn_t build_conn(const char* url) {
    conn_t conn;
    struct sockaddr_in remote_addr, local_addr;
    int sock = 0;
    
    conn.url_info = parse_url(url);
    
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(0);
    
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_addr.s_addr = inet_addr(conn.url_info.host);
    remote_addr.sin_port = htons(conn.url_info.port);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    ASSERT_EXIT(sock >= 0, "socket create failed");
    
    conn.sock = sock;
    ASSERT_EXIT(bind(conn.sock, (struct sockaddr*)&local_addr,sizeof(local_addr)) >= 0, "bind error");
    
    if (connect(conn.sock, (struct sockaddr*)&remote_addr, sizeof(remote_addr)) >= 0) {
        conn.avaliable = 1;
    }
    return conn;
}

