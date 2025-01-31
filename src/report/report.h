#ifndef REPORT_H
#define REPORT_H

#include "../inventory/inventory.h"
#include <stdio.h>
#include "../lib/lib.h"

/**
 * @brief Checks if an inventory item needs to be reordered
 * @param node Pointer to the inventory node to check
 * @return 1 if item quantity is at or below reorder level, 0 otherwise
 */
int should_report_item(InventoryNode *node);

/**
 * @brief Collects inventory items that need to be reordered
 * @param node Pointer to the first node in the inventory list
 * @return NULL-terminated array of pointers to reportable items, or NULL on
 * error
 */
InventoryItem **collect_reportable_items(InventoryNode *node);

/**
 * @brief Writes a single inventory item to the report file
 * @param fp File pointer to write to
 * @param item Pointer to inventory item to write
 * @return Number of characters written, or negative on error
 */
int write_report_txt_line(FILE *fp, InventoryItem *item);

/**
 * @brief Writes reorder report files in text and JSON format
 * @param items NULL-terminated array of pointers to inventory items
 * @return 0 on success, -1 on error
 */
int write_report_files(InventoryItem **items);

#endif
