
#ifndef FS_H
#define FS_H

#include "../vars.h"

void create_directory_if_not_exists(const char *path);
char *get_data_directory();
char *get_full_path(const char *filename);
void write_to_file(const char *filename, const char *content);

#endif
