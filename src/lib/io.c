#include "io.h"
#include "log.h"
#include <stdlib.h>
#include <sys/stat.h>

int check_path_exists(char *path) {
  if (!path) {
    LOG_ERR("Path is NULL");
    return 0;
  }

  struct stat st;
  if (stat(path, &st) == 0) {
    return 1;
  }
  return 0;
}

int check_file_exists(char *filename) {
  if (!filename) {
    LOG_ERR("Filename is Null");
    return 0;
  }

  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    fclose(file);
    return 1;
  }
  return 0;
}

int read_file(const char *file_path, char **buffer, long *file_size) {
  FILE *file = fopen(file_path, "r");
  if (!file) {
    LOG_ERR("Failed to open file %s", file_path);
    return 0;
  }

  fseek(file, 0, SEEK_END);
  *file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  *buffer = (char *)malloc(*file_size + 1);
  if (!*buffer) {
    LOG_ERR("Memory allocation failed for file %s", file_path);
    fclose(file);
    return 0;
  }

  fread(*buffer, 1, *file_size, file);
  (*buffer)[*file_size] = '\0';

  fclose(file);
  return 1;
}
