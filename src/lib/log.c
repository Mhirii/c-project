#include "log.h"
#include "../config/config.c"
#include "../lib/vars.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *level_to_string(enum log_levels level) {
  switch (level) {
  case DEBUG:
    return "DEBUG";
    break;
  case INFO:
    return "INFO";
    break;
  case WARN:
    return "WARN";
    break;
  case ERROR:
    return "ERROR";
    break;
  case FATAL:
    return "FATAL";
    break;
  }
  return "UNKNOWN";
}

int print_log(struct Log *log) {
  if (!log || !log->timestamp || !log->message) {
    return -1;
  }

  char *level = level_to_string(log->level);
  if (!level) {
    return -1;
  }

  size_t log_line_size =
      strlen(log->timestamp) + strlen(level) + strlen(log->message) + 6;

  char *log_line = malloc(log_line_size);
  if (!log_line) {
    return -1;
  }

  if (snprintf(log_line, log_line_size, "[%s] %s  %s\n", log->timestamp, level,
               log->message) < 0) {
    free(log_line);
    return -1;
  }

  FILE *log_file = fopen(global_log_file_path, "a");
  if (!log_file) {
    free(log_line);
    return -1;
  }

  fprintf(log_file, "%s\n", log_line);
  if (log->level >= 3) {
    fprintf(stderr, "%s\n", log_line);
  } else {
    printf("%s\n", log_line);
  }

  fclose(log_file);
  free(log_line);
  return 0;
}

struct Log *new_log(enum log_levels level, char *message) {
  if (!message) {
    return NULL;
  }

  struct Log *log = malloc(sizeof(struct Log));
  if (!log) {
    return NULL;
  }

  time_t t = time(NULL);
  char *timestamp = ctime(&t);
  if (!timestamp) {
    free(log);
    return NULL;
  }

  // timestramp will have newline by default, we remove it
  timestamp[strlen(timestamp) - 1] = '\0';

  // Allocate and copy timestamp and message
  log->timestamp = strdup(timestamp);
  if (!log->timestamp) {
    free(log);
    return NULL;
  }
  log->message = strdup(message);
  if (!log->message) {
    free(log->timestamp);
    free(log);
    return NULL;
  }

  log->level = level;

  return log;
}

void Log(enum log_levels level, char *message) {
  struct Log *log = new_log(level, message);
  print_log(log);
}
