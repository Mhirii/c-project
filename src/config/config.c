#include "config.h"
#include "../json/json.h"
#include "../lib/lib.h"
#include <stdlib.h>
#include <string.h>

Config *parse_config(const char **buffer) {
  LOG(0, "Initiating Config Parser");
  int *isErr = malloc(sizeof(int));
  Config *config = (Config *)malloc(sizeof(Config));

  if (config == NULL) {
    LOG_ERR("Error: Memory allocation failed.\n");
    return NULL;
  }

  memcpy(config, &DefaultConfig, sizeof(Config));

  CHECK_ERROR((!parse_json_object(buffer)), "Invalid JSON object\n");

  while (**buffer != '}') {
    char *key = NULL;
    CHECK_ERROR((!parse_json_key(buffer, &key)), "Failed to parse key");

    CHECK_ERROR((!parse_json_key_value_separator(buffer)),
                "Failed to parse key-value separator");

    if (strcmp(key, "low_stock_threshold") == 0) {
      CHECK_ERROR((!parse_json_number(buffer, &config->low_stock_threshold)),
                  "Failed to parse low_stock_threshold");
      LOG(0, "low_stock_threshold: %d", config->low_stock_threshold);

    } else if (strcmp(key, "auto_reorder") == 0) {
      CHECK_ERROR((!parse_json_number(buffer, &config->auto_reorder)),
                  "Failed to parse auto_reorder");
      LOG(0, "auto_reorder: %d", config->auto_reorder);

    } else if (strcmp(key, "log_file_path") == 0) {
      char *log_path = NULL;
      CHECK_ERROR((!parse_json_string(buffer, &log_path)),
                  "Failed to parse log_file_path");

      strncpy(config->log_file_path, log_path, MAX_NAME_LENGTH - 1);
      config->log_file_path[MAX_NAME_LENGTH - 1] = '\0';

      free(log_path);
      LOG(0, "log_file_path: %s", config->log_file_path);

    } else if (strcmp(key, "report_generation_frequency") == 0) {
      CHECK_ERROR(
          (!parse_json_number(buffer, &config->report_generation_frequency)),
          "Failed to parse report_generation_frequency");
      LOG(0, "report_generation_frequency: %d",
          config->report_generation_frequency);

    } else {
      LOG_ERR("Unknown key: %s, SKIPPING", key);
    }

    free(key);

    skip_whitespace(buffer);
    if (**buffer != '}') {

      CHECK_ERROR((!parse_json_value_separator(buffer)),
                  "Failed to parse value separator");
    }
  }
  return NULL;
}

Config *load_config(char *config_file_path) {
  LOG(0, "Loading config file: %s", config_file_path);
  const char *buffer = read_file(config_file_path);
  if (!buffer) {
    LOG_ERR("Failed to read config file %s", config_file_path);
    return NULL;
  }

  Config *config = parse_config(&buffer);
  free((void *)buffer);
  return config;
}
