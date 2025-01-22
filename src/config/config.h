#ifndef CONFIG_H
#define CONFIG_H
#include "../lib/vars.h"

struct Config {
    int low_stock_threshold;
    int auto_reorder;
    char log_file_path[MAX_NAME_LENGTH];
    int report_generation_frequency; // in days
} ;

#endif
