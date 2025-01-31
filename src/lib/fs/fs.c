#include "../log.h"
#include "../vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../config/config.h"
#include "../log.h"
#include "dirent.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#include <sys/stat.h> // mkdir on POSIX
#endif

#ifdef _WIN32
#include <direct.h> // _mkdir on Windows   yuck :v
#endif

void create_directory_if_not_exists(const char *path) {
#ifdef _WIN32
  _mkdir(path);
#else
  mkdir(path,
        0777); // 0777 for rwx to everyone
#endif
}

// OS-specific data dir
char *get_data_directory() {
  char *data_dir = NULL;

#ifdef _WIN32
  // %APPDATA%
  data_dir = getenv("APPDATA");
#elif __APPLE__
  // ~/Library/Application Support
  data_dir = getenv("HOME");
  if (data_dir != NULL) {
    char *mac_data_dir =
        malloc(strlen(data_dir) + strlen("/Library/Application Support") + 1);
    strcpy(mac_data_dir, data_dir);
    strcat(mac_data_dir, "/Library/Application Support");
    data_dir = mac_data_dir;
  }
#else
  // $XDG_DATA_HOME or fallback to ~/.local/share
  data_dir = getenv("XDG_DATA_HOME");
  if (data_dir == NULL) {
    data_dir = getenv("HOME");
    if (data_dir != NULL) {
      char *linux_data_dir =
          malloc(strlen(data_dir) + strlen("/.local/share") + 1);
      strcpy(linux_data_dir, data_dir);
      strcat(linux_data_dir, "/.local/share");
      data_dir = linux_data_dir;
    }
  }
#endif

  return data_dir;
}

char *get_full_path(const char *filename) {
  char *data_dir = get_data_directory();
  if (data_dir == NULL) {
    LOG_ERR("Error: Could not determine data directory.\n");
    return NULL;
  }

  char app_dir[256];
  snprintf(app_dir, sizeof(app_dir), "%s/%s", data_dir, APP_NAME);
  create_directory_if_not_exists(app_dir);

  char *full_path =
      malloc(strlen(app_dir) + strlen(filename) + 2); // +2 => '/' and '\0'
  if (full_path == NULL) {
    LOG_ERR("Error: Memory allocation failed.\n");
    return NULL;
  }
  sprintf(full_path, "%s/%s", app_dir, filename);

// Free mem for data_dir
#ifdef __APPLE__
  free(data_dir);
#elif !defined(_WIN32) && !defined(__APPLE__)
  if (getenv("XDG_DATA_HOME") == NULL) {
    free(data_dir);
  }
#endif

  return full_path;
}

void write_to_file(const char *filename, const char *content) {
  char *full_path = get_full_path(filename);
  if (full_path == NULL) {
    return;
  }

  FILE *file = fopen(full_path, "w");
  if (file == NULL) {
    LOG_ERR("Error: Could not open file for writing.\n");
    free(full_path);
    return;
  }

  fprintf(file, "%s", content);
  fclose(file);

  printf("File saved to: %s\n", full_path);

  free(full_path);
}

int create_file_if_not_exists(const char *path) {
  FILE *file = fopen(path, "a");
  if (file == NULL) {
    LOG_ERR("Error: Could not open file for writing.\n");
    return 0;
  }

  fclose(file);

  LOG(0, "File created at: %s\n", path);

  return 1;
}

int data_dir_exists() {
  char *data_dir = config.data_path;
  DIR *dir = opendir(data_dir);
  if (dir == NULL) {
    return 0;
  }
  closedir(dir);
  return 1;
}

int data_dir_has_dir(const char *dirname) {
  char *data_dir = config.data_path;
  DIR *dir = opendir(data_dir);
  if (dir == NULL) {
    return 0;
  }
  struct dirent *ent;
  while ((ent = readdir(dir)) != NULL) {
    if (strcmp(ent->d_name, dirname) == 0) {
      closedir(dir);
      return 1;
    }
  }
  closedir(dir);
  return 0;
}

int dir_has_file(char *dir_path, char *filename) {
  DIR *dir = opendir(dir_path);
  if (dir == NULL) {
    LOG_ERR("dir was null");
    return 0;
  }
  struct dirent *ent;
  while ((ent = readdir(dir)) != NULL) {
    if (strcmp(ent->d_name, filename) == 0) {
      closedir(dir);
      return 1;
    }
  }
  closedir(dir);
  return 0;
}

int create_data_dir() {
  if (!data_dir_exists()) {
    create_directory_if_not_exists(config.data_path);
    return 1;
  }
  return 0;
}

int create_dir_in_data(const char *dirname) {
  if (!data_dir_has_dir(dirname)) {
    char *dir_path = malloc(strlen(config.data_path) + strlen(dirname) + 2);
    sprintf(dir_path, "%s/%s", config.data_path, dirname);
    create_directory_if_not_exists(dir_path);
    free(dir_path);
    return 1;
  }
  return 0;
}

int create_file(char *dirname, char *filename) {
  if (!dir_has_file(dirname, filename)) {

    char *file_path = malloc(strlen(dirname) + strlen(filename) + 2);
    sprintf(file_path, "%s/%s", dirname, filename);
    write_to_file(file_path, "\n");
    create_file_if_not_exists(file_path);

    free(file_path);
    return 1;
  }
  return 0;
}

char *create_path(const char *str1, const char *str2) {
  if (!str1 || !str2)
    return NULL;

  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);
  size_t total_len = len1 + len2 + 2;

  char *result = malloc(total_len);
  if (!result)
    return NULL;

  snprintf(result, total_len, "%s/%s", str1, str2);
  return result;
}
