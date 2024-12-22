#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *LOG_TYPES[] = {"INFO ", "WARN ", "ERROR", "DEBUG"};
const char *LOG_COLORS[] = {"\033[32mINFO\033[0m ", "\033[33mWARN\033[0m ",
                            "\033[31mERROR\033[0m", "\033[36mDEBUG\033[0m"};

time_t getTime() {
  time_t rawtime;
  struct tm *timeinfo;
  if (time(&rawtime) == -1) {
    return -1;
  }
  timeinfo = localtime(&rawtime);
  if (timeinfo == NULL) {
    return -1;
  }
  time_t result = mktime(timeinfo);
  if (result == -1) {
    return -1;
  }
  return result;
}

char *timeToString(time_t time) {
  struct tm *timeinfo = localtime(&time);
  if (timeinfo == NULL) {
    return NULL;
  }

  char *timeStr = malloc(22 * sizeof(char)); // DD/MM/YYYY HH:MM:SS\0
  if (timeStr == NULL) {
    return NULL;
  }

  snprintf(timeStr, 22, "%02d/%02d/%04d %02d:%02d:%02d", timeinfo->tm_mday,
           timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour,
           timeinfo->tm_min, timeinfo->tm_sec);

  return timeStr;
}

struct Log *createLog(enum LogType type, char *message) {
  if (message == NULL) {
    return NULL;
  }

  struct Log *log = malloc(sizeof(struct Log));
  if (log == NULL) {
    return NULL;
  }

  time_t time_now = getTime();
  if (time_now == -1) {
    free(log);
    return NULL;
  }
  char *timestamp = timeToString(time_now);

  log->timestamp = timestamp;
  log->message = message;
  log->type = type;
  return log;
};

struct Log *CreateErrorLog(char *message) { return createLog(ERROR, message); }

struct Log *CreateInfoLog(char *message) { return createLog(INFO, message); }
void Info(char *message) { PrintLog(CreateInfoLog(message)); }

struct Log *CreateWarnLog(char *message) { return createLog(WARN, message); }
void Warn(char *message) { PrintLog(CreateWarnLog(message)); }

struct Log *CreateDebugLog(char *message) { return createLog(DEBUG, message); }
void Debug(char *message) { PrintLog(CreateDebugLog(message)); }

void PrintLog(struct Log *log) {
  if (log == NULL) {
    return;
  }
  switch (log->type) {
  case ERROR:
    fprintf(stderr, "[%s] \033[31mERROR\033[0m %s\n", log->timestamp,
            log->message);
    break;
  default:
    fprintf(stdout, "[%s] %s %s\n", log->timestamp, LOG_COLORS[log->type],
            log->message);
    break;
  }
}
