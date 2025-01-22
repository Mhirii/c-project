#ifndef IO_H
#define IO_H

#include <stdio.h>

FILE *open_file(char *filename, char *mode);
char *read_file(FILE *file);
void close_file(FILE *file);

int check_path_exists(char *path);
int check_file_exists(char *filename);

#endif
