#include "io.h"
#include "log.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
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

int write_file(const char *file_path, char *buffer) {
  FILE *file = fopen(file_path, "w");
  if (!file) {
    LOG_ERR("Failed to open file %s", file_path);
    return 0;
  }

  fwrite(buffer, 1, strlen(buffer), file);
  fclose(file);
  return 1;
}

int delete_file(const char *file_path) {
  if (!file_path) {
    LOG_ERR("File path is NULL");
    return 0;
  }

  if (remove(file_path) != 0) {
    LOG_ERR("Failed to delete file %s", file_path);
    return 0;
  }
  return 1;
}

/**
 * @brief Lists all JSON files in a directory
 * @param path The dir path
 * @param files arr that stores paths of JSON files
 * @return -1 on error or Number of JSON files found.
 */
int ls_json_files(const char *path, char **files) {
  DIR *dir;
  struct dirent *entry;
  int i = 0;

  dir = opendir(path);
  if (dir == NULL) {
    LOG_ERR("Unable to open directory at %s", path);
    return -1;
  }

  while ((entry = readdir(dir)) != NULL) {
    const char *ext = strrchr(entry->d_name, '.');
    if (ext && strcmp(ext, ".json") == 0) {
      if (files == NULL) {
        LOG_ERR("files array is NULL");
        continue;
      }

      char *full_path = malloc(strlen(path) + strlen(entry->d_name) +
                               2); // +2 for '/' and null terminator
      if (full_path == NULL) {
        LOG_ERR("Failed to allocate memory for full path");
        continue;
      }

      if (sprintf(full_path, "%s/%s", path, entry->d_name) < 0) {
        LOG_ERR("Error occurred while formatting full_path, name = %s",
                entry->d_name);
        free(full_path);
      } else {
        files[i] = full_path;
        i++;
      };
    }
  }

  closedir(dir);

  return i;
}
