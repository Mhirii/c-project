#include "errors.h"
#include "log.h"
#include <stdlib.h>

struct Error *createError(char *message) {
  struct Error *err = malloc(sizeof(struct Error));
  err->message = message;
  return err;
}

void LogError(struct Error *err) {
  struct Log *errLog = CreateErrorLog(err->message);
  PrintLog(errLog);
}

void PanicError(struct Error *err) {
  LogError(err);
  exit(EXIT_FAILURE);
}
