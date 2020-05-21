/*
 * FILE: download.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: download file
 */

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <pthread.h>
#include <stdio.h>
#define MAX_RECV_SIZE 1024

typedef struct thread_info_s {
    int start;
    unsigned long limit;
    int num; //thread serial number
    char* url;
    pthread_mutex_t* mutex_lock;
    FILE* fw;
} thread_info_t;

//void* download_range(void* arg);

void info_free(thread_info_t** infos, const int thread_num);

#endif
