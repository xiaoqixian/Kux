/*
 * FILE: parse.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 */

#include "parse.h"

/*
 * http url example:
 * https://pic4.zhimg.com/50/v2-a802ae4594efb3f3402871fcd4b83948_hd.jpg
 */

url_t parse_url(const char* url) {
    url_t url_info = {0};
    int i = 0, j = 0;
    char host[256] = {0};
    char IP[32] = {0};
    struct hostent* hsptr;
    
    //parse http protocol to decide if scheme is http or https
    while (url[i] != ':') {
        url_info.scheme[j++] = url[i++];
    }
    DEBUG("url scheme: %s", url_info.scheme);

    //parse host
    j = 0;
    i += 3;
    while (url[i] != ':' && url[i] != '/' && url[i] != 0) {
        host[j++] = url[i++];
    }
    DEBUG("host: %s", host);
    strcpy(url_info.host_name, host);
    
    //parse port
    if (url[i] == ':') {
        i++;
        j = 0;
        char tmp_port[8] = {0};
        while (url[i] != '/') {
            tmp_port[j++] = url[i++];
        }
        sscanf(tmp_port, "%d", &url_info.port);
    }
    else {
        url_info.port = 80;
    }
    DEBUG("url port: %d", url_info.port);
    
    //parse file path
    if (url[i] != 0) {
        j = 0;
        while (url[i] != 0) {
            url_info.file[j++] = url[i++];
        }
    }
    else {
        url_info.file[0] = '/';
    }
    DEBUG("url file path: %s", url_info.file);

    //gethostbyname
    hsptr = gethostbyname(host);
    
    if (hsptr != NULL) {
        strcpy(url_info.host, inet_ntop(hsptr->h_addrtype, *(hsptr->h_addr_list), IP, sizeof(IP)));
        DEBUG("url host: %s", url_info.host);
    }
    else {
        LOG_ERR("gethostbyname");
    }
    
    return url_info;
}
