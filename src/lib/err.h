#ifndef ERR_H
#define ERR_H

struct Error {
	char *message;
};

struct Error *create_error(char *message);
void log_error(char *message);
void panic_error(char *message);


#endif
