#ifndef LOGS_H
#define LOGS_H

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

namespace logs {
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
} // namespace render

#endif