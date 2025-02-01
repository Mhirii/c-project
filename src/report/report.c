#include "report.h"
#include "../inventory/inventory.h"
#include "html.c"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int should_report_item(InventoryNode *node) {
  return (node->data.quantity <= node->data.reorder_level);
}

InventoryItem **collect_reportable_items(InventoryNode *node) {
  if (!node) {
    return NULL;
  }

  int count = 0;
  InventoryNode *current = node;
  while (current != NULL) {
    if (should_report_item(current)) {
      count++;
    }
    current = current->next;
  }

  InventoryItem **items = malloc(sizeof(InventoryItem *) * (count + 1));
  if (!items) {
    return NULL;
  }

  current = node;
  int i = 0;
  while (current != NULL && i < count) {
    if (should_report_item(current)) {
      items[i] = &(current->data);
      i++;
    }
    current = current->next;
  }
  items[count] = NULL;

  return items;
}

int write_report_txt_line(FILE *fp, InventoryItem *item) {
  int needed = item->reorder_level - item->quantity;
  return fprintf(
      fp,
      "id=%d\tname=%s\tquantity=%d\treorder_level=%d\tneeded=%d\tcontact=%d\n",
      item->id, item->name, item->quantity, item->reorder_level, needed,
      item->supplier_id);
}

int empty_dir(char *path) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (dir == NULL) {
    LOG_ERR("Unable to open directory at %s", path);
    return -1;
  }

  while ((entry = readdir(dir)) != NULL) {
    char *full_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
    if (full_path == NULL) {
      LOG_ERR("Failed to allocate memory for full path");
      continue;
    }

    sprintf(full_path, "%s/%s", path, entry->d_name);
    if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
      if (remove(full_path) != 0) {
        LOG_ERR("Failed to delete file: %s", full_path);
      }
    }
    free(full_path);
  }

  closedir(dir);

  return 0;
}

int write_report_files(InventoryItem **items) {

  create_directory_if_not_exists("report");
  empty_dir("report");

  FILE *fp = fopen("report/reorder.txt", "w");
  if (!fp) {
    LOG_ERR("Failed to open file");
    return -1;
  }

  int i = 0;
  while (items[i] != NULL) {
    write_report_txt_line(fp, items[i]);
    write_item_json(items[i], "report");
    i++;
  }

  char *html = generate_html_page(items, i);
  if (html) {
    write_file("report/reorder.html", html);
    free(html);
  } else {
    LOG_ERR("Failed to generate HTML page");
  }

  fclose(fp);
  return 0;
}

int write_report(Memo *memo) {
  InventoryItem **items = collect_reportable_items(memo->inventory->head);
  return write_report_files(items);
}
