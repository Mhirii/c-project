#ifndef IO_H
#define IO_H

#include <stdio.h>


int check_path_exists(char *path);
int check_file_exists(char *filename);

int read_file(const char *file_path, char **buffer, long *file_size);
int write_file(const char *file_path, char *buffer);
int delete_file(const char *file_path);
int ls_json_files(const char *path, char **files);

#endif
