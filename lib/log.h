
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

void PrintLog(struct Log *log);

struct Log *CreateErrorLog(char *message);
struct Log *CreateInfoLog(char *message);
struct Log *CreateWarnLog(char *message);
struct Log *CreateDebugLog(char *message);

#endif
