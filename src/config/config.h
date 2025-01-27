#ifndef CONFIG_H
#define CONFIG_H
#include "../lib/vars.h"

typedef struct {
    int low_stock_threshold;
    int auto_reorder;
    char log_file_path[MAX_NAME_LENGTH];
    int report_generation_frequency; // in days
}Config;

const Config DefaultConfig = {10, 0, "default.log", 1};

Config *parse_config(const char **buffer);
Config *load_config(char *config_file_path);

#endif
