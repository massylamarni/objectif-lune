#include "logs.h"

namespace output {
static void log_to_file(FILE *file, const char *fmt, va_list args) {
  if (!file)
    return;

  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);

  char buffer[TIME_BUFFER_SIZE];
  strftime(buffer, TIME_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", tm_info);

  fprintf(file, "[%s] ", buffer);
  vfprintf(file, fmt, args);
  fprintf(file, "\n");
  fflush(file);
}

Logger init() {
  if (mkdir("logs", 0755) != 0 && errno != EEXIST) {
    printf("Failed to create logs directory due to missing permissions, please create it in at the root of the project, exiting...\n");
    exit(1);
  }

  Logger logger;
  logger.general = fopen("logs/general.log", "w");
  logger.render = fopen("logs/render.log", "w");
  logger.errors = fopen("logs/errors.log", "w");

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

output::Logger *get_logger() {
  static output::Logger logger;
  static bool initialized = false;
  if (!initialized) {
    logger = output::init();
    initialized = true;
  }
  return &logger;
}
} // namespace output