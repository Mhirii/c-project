
#ifndef errorpkg
#define errorpkg

// TODO: add traces
struct Error {
  char *message;
};

struct Error *create_error(char *message);
void log_error(struct Error *err);
void panic_error(struct Error *error);

#endif
