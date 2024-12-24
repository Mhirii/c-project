#include "errors.h"
#include "log.h"
#include <stdlib.h>

struct Error *create_error(char *message) {
  struct Error *err = malloc(sizeof(struct Error));
  err->message = message;
  return err;
}

void log_error(struct Error *err) {
  struct Log *errLog = create_error_log(err->message);
  print_log(errLog);
}

void panic_error(struct Error *err) {
  log_error(err);
  exit(EXIT_FAILURE);
}
