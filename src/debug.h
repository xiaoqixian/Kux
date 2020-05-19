/*
 * FILE: debug.h
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Kux
 * Description: macro functions for debug
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#ifdef NDEBUG
#define DEBUG(M, ...)

#else
#define DEBUG(M, ...) fprintf(stderr, "[DEBUG](%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define CLEAN_ERRNO() (errno == 0 ? "None" : strerror(errno))

#define LOG_INFO(M, ...) fprintf(stderr, "[INFO](%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define LOG_ERR(M, ...) fprintf(stderr, "[ERROR](%s:%d) errno: %s" M "\n",     __FILE__, __LINE__,CLEAN_ERRNO(), ##__VA_ARGS__)

#define ASSERT(A, M, ...) if (!(A)) {LOG_ERR(M "\n", ##__VA_ARGS__);}

#define ASSERT_EXIT(A, M, ...) if (!(A)) {LOG_ERR(M "\n", ##__VA_ARGS__);exit(1);}

#endif
