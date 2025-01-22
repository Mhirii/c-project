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

char *read_file(const char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = (char *)malloc(file_size + 1);
  if (!content) {
    fclose(file);
    return NULL;
  }

  fread(content, 1, file_size, file);
  content[file_size] = '\0';

  fclose(file);
  return content;
}
