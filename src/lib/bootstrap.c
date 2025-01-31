
#include "bootstrap.h"
#include "../report/report.h"
#include "fs/fs.h"
#include "log.h"
#include <stdlib.h>

int setup_data_files() {
  create_data_dir();

  const char *dirs[] = {"inventory", "order", "supplier"};
  for (int i = 0; i < sizeof(dirs) / sizeof(dirs[0]); i++) {
    if (create_dir_in_data(dirs[i])) {

      LOG(1, "%s dir created", dirs[i]);
    }

    char *path = create_path(config.data_path, dirs[i]);
    if (path) {
      if (create_file(path, "metadata")) {
        LOG(1, "metadata file created at %s", path);
      }
      free(path);
    } else {
      LOG_ERR("Error creating path");
      return -1;
    }
  }

  return 0;
}

int bootstrap() {

  load_config("config.json");
  LOG(1, "Loaded Config");

  if (setup_data_files() == -1)
    return -1;

  return 0;
}
