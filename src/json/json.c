#include "json.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void skip_whitespace(const char **json) {
  while (isspace(**json)) {
    (*json)++;
  }
}

int parse_json_string(const char **json, char **str) {
  skip_whitespace(json);
  if (**json != '"')
    return 0; // Expect a double quote
  (*json)++;

  const char *start = *json;
  while (**json != '"' && **json != '\0')
    (*json)++;
  if (**json != '"')
    return 0; // Missing closing quote

  long length = *json - start;
  *str = malloc(length + 1);
  memcpy(*str, start, length);
  (*str)[length] = '\0';
  (*json)++;
  return 1;
}

int parse_json_number(const char **json, int *num) {
  skip_whitespace(json);
  char *end;
  *num = strtol(*json, &end, 10);
  if (*json == end)
    return 0;
  *json = end;
  return 1;
}

int parse_json_float(const char **json, float *num) {
  skip_whitespace(json);
  char *end;
  *num = strtof(*json, &end);
  if (*json == end)
    return 0;
  *json = end;
  return 1;
}

int parse_json_bool(const char **json, int *num) {
  skip_whitespace(json);
  if (strncmp(*json, "true", 4) == 0) {
    *num = 1;
    *json += 4;
    return 1;
  } else if (strncmp(*json, "false", 5) == 0) {
    *num = 0;
    *json += 5;
    return 1;
  }
  return 0;
}

int parse_json_null(const char **json, int *num) {
  skip_whitespace(json);
  if (strncmp(*json, "null", 4) == 0) {
    *num = 0;
    *json += 4;
    return 1;
  }
  return 0;
}
