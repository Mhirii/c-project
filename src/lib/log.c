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
    return "INFO ";
    break;
  case WARN:
    return "WARN ";
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

char *color_level(enum log_levels level) {
  switch (level) {
  case DEBUG:
    return "\033[30;43mDEBUG\033[0m"; // Black text on orange background for
                                      // debug level
    break;
  case INFO:
    return "\033[32mINFO \033[0m"; // Green for normal info
    break;
  case WARN:
    return "\033[33mWARN \033[0m"; // Yellow for warnings
    break;
  case ERROR:
    return "\033[91mERROR\033[0m"; // Bright red for errors
    break;
  case FATAL:
    return "\033[97;41mFATAL\033[0m"; // White text on red background for fatal
    break;
  }
  return "\033[37mUNKNOWN\033[0m";
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
  char *colored_log_line = malloc(log_line_size + 20);

  if (!log_line) {
    return -1;
  }

  if (snprintf(log_line, log_line_size, "[%s] %s  %s\n", log->timestamp, level,
               log->message) < 0) {
    free(log_line);
    return -1;
  }
  if (snprintf(colored_log_line, log_line_size + 20, "[%s] %s  %s\n",
               log->timestamp, color_level(log->level), log->message) < 0) {
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
    fprintf(stderr, "%s\n", colored_log_line);
  } else {
    printf("%s\n", colored_log_line);
  }

  fclose(log_file);
  free(log_line);
  free(colored_log_line);
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
