
#ifndef logpkg
#define logpkg
#include <time.h>

enum LogType {
    INFO = 0,
    WARN = 1,
    ERROR = 2,
    DEBUG = 3
};

struct Log {
	char* timestamp;
	enum LogType type;
    char *message;
};

void print_log(struct Log *log);

struct Log *create_error_log(char *message);
struct Log *create_info_log(char *message);
struct Log *create_warn_log(char *message);
struct Log *create_debug_log(char *message);

#endif
