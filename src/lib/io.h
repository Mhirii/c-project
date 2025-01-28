#ifndef IO_H
#define IO_H

#include <stdio.h>


int check_path_exists(char *path);
int check_file_exists(char *filename);

int read_file(const char *file_path, char **buffer, long *file_size);
int write_file(const char *file_path, char *buffer);

#endif
