#ifndef IO_H
#define IO_H

#include <stdio.h>


int check_path_exists(char *path);
int check_file_exists(char *filename);

char *read_file(const char *path);

#endif
