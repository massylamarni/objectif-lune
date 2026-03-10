#include "logs.h"

namespace logs {
static void log_to_file(FILE *file, const char *fmt, va_list args) {
  if (!file)
    return;

  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);

  const int TIME_BUFFER_SIZE = 26;
  char buffer[TIME_BUFFER_SIZE];
  strftime(buffer, TIME_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", tm_info);

  fprintf(file, "[%s] ", buffer);
  vfprintf(file, fmt, args);
  fprintf(file, "\n");
  fflush(file);
}

Logger init() {
  Logger logger;
  logger.general = fopen("general.log", "a");
  logger.render = fopen("render.log", "a");
  logger.errors = fopen("errors.log", "a");

  if (!logger.general) {
    printf("Failed to open general log file, exiting...\n");
    exit(1);
  }
  if (!logger.render) {
    printf("Failed to open render log file, exiting...\n");
    exit(1);
  }
  if (!logger.errors) {
    printf("Failed to open errors log file, exiting...\n");
    exit(1);
  }

  return logger;
}

void close(Logger *logger) {
  if (!logger)
    return;

  if (logger->general)
    fclose(logger->general);
  if (logger->render)
    fclose(logger->render);
  if (logger->errors)
    fclose(logger->errors);

  logger->general = NULL;
  logger->render = NULL;
  logger->errors = NULL;
}

void log(Logger *logger, const char *fmt, ...) {
  if (!logger || !logger->general)
    return;
  va_list args;
  va_start(args, fmt);
  log_to_file(logger->general, fmt, args);
  va_end(args);
}

void log_render(Logger *logger, const char *fmt, ...) {
  if (!logger || !logger->render)
    return;
  va_list args;
  va_start(args, fmt);
  log_to_file(logger->render, fmt, args);
  va_end(args);
}

void log_error(Logger *logger, const char *fmt, ...) {
  if (!logger || !logger->errors)
    return;
  va_list args;
  va_start(args, fmt);
  log_to_file(logger->errors, fmt, args);
  va_end(args);
}
} // namespace render