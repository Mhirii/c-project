#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG_ERR(fmt, ...) \
    do { \
        char log_buffer[1024]; \
        snprintf(log_buffer, sizeof(log_buffer), "file=%s:%d fn=%s msg=" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
        struct Log* log = new_log(3, log_buffer); \
        print_log(log); \
    } while (0)

#define LOG(level, fmt, ...)\
do { \
    char log_buffer[1024]; \
    snprintf(log_buffer, sizeof(log_buffer), "file=%s:%d fn=%s msg=" fmt, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    struct Log* log = new_log(level, log_buffer); \
    print_log(log); \
} while (0)


enum log_levels{
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
};

struct Log{
	char *timestamp;
    enum log_levels level;
    char *message;
};

char* level_to_string(enum log_levels level);
int print_log(struct Log *log);
struct Log *new_log(enum log_levels level, char *message);

void Log(enum log_levels level, char *message);

#endif
