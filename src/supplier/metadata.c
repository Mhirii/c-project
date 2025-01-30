#include "../config/config.h"
#include "../lib/lib.h"
#include "supplier.h"
#include <stdlib.h>
#include <string.h>

int write_supp_metadata(char *path, SupplierList *list) {
  char *buffer = malloc(64);
  sprintf(buffer, "last_id=%d\nsize=%d\n", list->last_id, list->size);
  if (!write_file(path, buffer)) {
    LOG_ERR("Error occurred while writing metadata file");
    return -1;
  }
  free(buffer);
  LOG(1, "Supplier Metadata file written");
  return 0;
}

int update_supp_metadata(SupplierList *list) {
  char *data_path =
      malloc(strlen(config.data_path) + strlen("/supplier/metadata") + 1);
  strcpy(data_path, config.data_path);
  char *path = strcat(data_path, "/supplier/metadata");

  if (write_supp_metadata(path, list) != 0) {
    LOG_ERR("Error writing updated supplier metadata");
    return -1;
  };
  return 0;
}

char *parse_supp_metadata_line(char *line) {
  char *key = strtok(line, "=");
  if (!key) {
    LOG_ERR("Failed to parse key");
    return NULL;
  }
  char *value = strtok(NULL, "\n");
  return value;
}

int parse_supp_metadata(char *path, SupplierList *list) {
  char *buffer = malloc(64);
  long file_size;
  if (!read_file(path, &buffer, &file_size)) {
    LOG_ERR("Error occurred while opening supplier metadata file");
    return -1;
  }

  char *line = strtok(buffer, "\n");
  while (line != NULL) {
    char *key = parse_supp_metadata_line(line);
    if (strcmp(key, "last_id") == 0) {
      int id = atoi(line);
      list->last_id = id;
    } else if (strcmp(key, "size") == 0) {
      int size = atoi(line);
      list->size = size;
    }
    line = strtok(NULL, "\n");
  }
  free((void *)buffer);
  LOG(1, "Metadata file read");
  return 0;
}
