
#ifndef errorpkg
#define errorpkg

// TODO: add traces
struct Error {
  char *message;
};

struct Error *createError(char *message);
void LogError(struct Error *err);
void PanicError(struct Error *error);

#endif
