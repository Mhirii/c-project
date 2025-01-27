#include "../vars.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // mkdir on POSIX

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
    fprintf(stderr, "Error: Could not determine data directory.\n");
    return NULL;
  }

  char app_dir[256];
  snprintf(app_dir, sizeof(app_dir), "%s/%s", data_dir, APP_NAME);
  create_directory_if_not_exists(app_dir);

  char *full_path =
      malloc(strlen(app_dir) + strlen(filename) + 2); // +2 => '/' and '\0'
  if (full_path == NULL) {
    fprintf(stderr, "Error: Memory allocation failed.\n");
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
    fprintf(stderr, "Error: Could not open file for writing.\n");
    free(full_path);
    return;
  }

  fprintf(file, "%s", content);
  fclose(file);

  printf("File saved to: %s\n", full_path);

  free(full_path);
}
