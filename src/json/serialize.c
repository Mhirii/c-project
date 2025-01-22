#include "../lib/vars.h"
#include "json.h"
#include <stdio.h>

void append_json_pair(char **json, const char *key, const char *value) {
  char pair[MAX_JSON_STRING_LENGTH];
  snprintf(pair, sizeof(pair), "\"%s\":%s", key, value);

  if (*json) {
    // +2 : 1 lel comma w 1 lel null
    *json = realloc(*json, strlen(*json) + strlen(pair) + 2);
    strcat(*json, ",");
  } else {
    *json = malloc(strlen(pair) + 1);
    strcpy(*json, "");
  }
  strcat(*json, pair);
}

void append_json_string_pair(char **json, const char *key, const char *value) {
  char string_value[MAX_JSON_STRING_LENGTH];
  snprintf(string_value, sizeof(string_value), "\"%s\"", value);
  append_json_pair(json, key, string_value);
}

void append_json_number_pair(char **json, const char *key, int value) {
  char number_value[64];
  snprintf(number_value, sizeof(number_value), "%d", value);
  append_json_pair(json, key, number_value);
}

void append_json_float_pair(char **json, const char *key, double value) {
  char float_value[64];
  snprintf(float_value, sizeof(float_value), "%.2f", value);
  append_json_pair(json, key, float_value);
}
