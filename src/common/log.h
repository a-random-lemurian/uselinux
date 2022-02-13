/**
 * Copyright (c) 2020 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define LOG_VERSION "0.1.0"

typedef struct
{
    va_list ap;
    const char *fmt;
    const char *file;
    struct tm *time;
    void *udata;
    int line;
    int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum
{
    LOGH_LOG_TRACE,
    LOGH_LOG_DEBUG,
    LOGH_LOG_INFO,
    LOGH_LOG_WARN,
    LOGH_LOG_ERROR,
    LOGH_LOG_FATAL
};

#define log_trace(...)                                                        \
    log_log(LOGH_LOG_TRACE, LOGGER_NAME, __LINE__, __VA_ARGS__)
#define log_debug(...)                                                        \
    log_log(LOGH_LOG_DEBUG, LOGGER_NAME, __LINE__, __VA_ARGS__)
#define log_info(...)                                                         \
    log_log(LOGH_LOG_INFO, LOGGER_NAME, __LINE__, __VA_ARGS__)
#define log_warn(...)                                                         \
    log_log(LOGH_LOG_WARN, LOGGER_NAME, __LINE__, __VA_ARGS__)
#define log_error(...)                                                        \
    log_log(LOGH_LOG_ERROR, LOGGER_NAME, __LINE__, __VA_ARGS__)
#define log_fatal(...)                                                        \
    log_log(LOGH_LOG_FATAL, LOGGER_NAME, __LINE__, __VA_ARGS__)

const char *log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif
