#include "report.h"
#include "../inventory/inventory.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Checks if an inventory item needs to be reordered
 * @param node Pointer to the inventory node to check
 * @return 1 if item quantity is at or below reorder level, 0 otherwise
 */
int should_report_item(InventoryNode *node) {
  return (node->data.quantity <= node->data.reorder_level);
}

/**
 * @brief Collects inventory items that need to be reordered
 * @param node Pointer to the first node in the inventory list
 * @return NULL-terminated array of pointers to reportable items, or NULL on
 * error
 */
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

/**
 * @brief Writes a single inventory item to the report file
 * @param fp File pointer to write to
 * @param item Pointer to inventory item to write
 * @return Number of characters written, or negative on error
 */
int write_report_txt_line(FILE *fp, InventoryItem *item) {
  return fprintf(fp,
                 "id=%d\tname=%s\tquantity=%d\treorder_level%d\tneedeed=%d\n",
                 item->id, item->name, item->quantity, item->reorder_level,
                 item->reorder_level - item->quantity);
}

/**
 * @brief Writes reorder report files in text and JSON format
 * @param items NULL-terminated array of pointers to inventory items
 * @return 0 on success, -1 on error
 */
int write_report_files(InventoryItem **items) {

  create_dir("report");
  FILE *fp = fopen("report/reorder.txt", "w");
  if (!fp) {
    return -1;
  }

  int i = 0;
  while (items[i] != NULL) {
    write_report_txt_line(fp, items[i]);
    write_item_json(items[i], "report");
    i++;
  }

  fclose(fp);
  return 0;
}
