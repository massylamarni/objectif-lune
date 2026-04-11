#ifndef LOGS_H
#define LOGS_H

#define LOG(msg, ...) output::log(output::get_logger(), msg, ##__VA_ARGS__)
#define LOG_RENDER(msg, ...) output::log_render(output::get_logger(), msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) output::log_error(output::get_logger(), msg, ##__VA_ARGS__)
#define DEBOUNCE_CAP 1048576      // Needs to be power of 2
#define LOGD(msg, ...)                                                         \
  do {                                                                         \
    static int _ctr = 0;                                                       \
    if ((_ctr++ & (DEBOUNCE_CAP - 1)) == 0)                                    \
      output::log(output::get_logger(), msg, ##__VA_ARGS__);                   \
  } while (0)
#define TIME_BUFFER_SIZE 26


#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

namespace output {
typedef struct Logger {
  FILE *general;
  FILE *render;
  FILE *errors;
} Logger;

Logger init(void);
void close(Logger *logger);
void log(Logger *logger, const char *fmt, ...);
void log_render(Logger *logger, const char *fmt, ...);
void log_error(Logger *logger, const char *fmt, ...);
output::Logger *get_logger();
} // namespace output

#endif