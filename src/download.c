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

int download_one_thread(const char* url) {
    conn_t conn = build_conn(url);
    while (!conn.avaliable) {
        sleep(1);
        conn = build_conn(url);
    }
    
    response_t resp;
    memset(&resp, 0, sizeof(response_t));
    parse_response(conn, url, &resp);
    
    FILE* fp;
    fp = fopen(resp.file_name, "rb+");
    ASSERT_EXIT(fp != NULL, "open file failed");
    fseek(fp, 0, 0);
    
    argu_t* arg = (argu_t*)malloc(sizeof(argu_t));
    memset(arg, 0, sizeof(argu_t));
    arg->start = 0;
    arg->limit = resp.file_size;

    send_request_range()
}
