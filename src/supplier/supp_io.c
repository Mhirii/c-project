#include "../config/config.h"
#include "../json/json.h"
#include "../lib/lib.h"
#include "supplier.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHK_ERR(condition, message)                                            \
  if (condition) {                                                             \
    LOG_ERR(message);                                                          \
    return -1;                                                                 \
  }

char *serialize_supp(Supplier supp) {
  char *json = NULL;

  json = malloc(2);
  strcpy(json, "{");

  append_json_number_pair(&json, "id", supp.id);
  append_json_string_pair(&json, "name", supp.first_name);
  append_json_string_pair(&json, "name", supp.last_name);
  append_json_string_pair(&json, "name", supp.email);
  append_json_string_pair(&json, "name", supp.phone);

  json = realloc(json, strlen(json) + 2);
  strcat(json, "}");

  return json;
}

int write_supp(Supplier *supp) {

  char filename[64];
  if (sprintf(filename, "%d.json", supp->id) < 0) {
    LOG_ERR("Error while formatting filename");
    return -1;
  }

  char *path = malloc(strlen(config.data_path) + strlen("/supplier") +
                      strlen(filename) + 2);
  if (!sprintf(path, "%s/supplier/%s", config.data_path, filename)) {
    LOG_ERR("Error while path to save supplier");
    return -1;
  }

  char *buffer = serialize_supp(*supp);
  if (!buffer) {
    LOG_ERR("Failed to serialize supplier");
    free(path);
    return -1;
  }

  int result = write_file(path, buffer) ? 0 : -1;
  free(buffer);

  if (result == -1) {
    free(path);
    LOG_ERR("Failed to write supplier file");
  }
  return result;
}

int read_supp(char *path, Supplier *supp) {
  char *buffer = NULL;
  long file_size;
  if (!read_file(path, &buffer, &file_size)) {
    LOG_ERR("Error occurred while opening file %s", path);
    return -1;
  }
  const char *ptr = buffer;

  CHK_ERR((!parse_json_object(&ptr)), "Invalid JSON object");

  while (*ptr != '}') {
    char *key = NULL;
    CHK_ERR((!parse_json_key(&ptr, &key)), "Failed to parse key");

    CHK_ERR((!parse_json_key_value_separator(&ptr)),
            "Failed to parse key-value separator");

    if (strcmp(key, "id") == 0) {
      CHK_ERR((!parse_json_number(&ptr, &(supp->id))), "Failed to parse id");

    } else if (strcmp(key, "first_name") == 0) {
      CHK_ERR((!parse_json_string(&ptr, &(supp->first_name))),
              "Failed to parse first_name");

    } else if (strcmp(key, "last_name") == 0) {
      CHK_ERR((!parse_json_string(&ptr, &(supp->last_name))),
              "Failed to parse last_name");

    } else if (strcmp(key, "email") == 0) {
      CHK_ERR((!parse_json_string(&ptr, &(supp->email))),
              "Failed to parse email");

    } else if (strcmp(key, "phone") == 0) {
      CHK_ERR((!parse_json_string(&ptr, &(supp->phone))),
              "Failed to parse phone");

    } else {
      LOG_ERR("Unknown key: %s", key);
      return -1;
    }

    free(key);

    skip_whitespace(&ptr);
    if (*ptr != '}') {

      CHK_ERR((!parse_json_value_separator(&ptr)),
              "Failed to parse value separator");
    }
  }

  CHK_ERR((!parse_json_object_end(&ptr)), "Failed to parse object end");

  return 0;
}
