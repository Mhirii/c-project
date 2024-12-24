#include "item.h"
#include "../lib/errors.h"
#include "../lib/terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

const char *ACCENT = "\033[1;36m";
const char *RESET = "\033[0m";

struct Item *create_item(int ID, int quantity, float price, char *name,
                         char *description) {
  if (ID < 0 || quantity < 0 || price < 0.0 || name == NULL ||
      description == NULL) {
    struct Error *error = create_error("Bad arguemnts provided");
    log_error(error);
    return NULL;
  }

  struct Item *item = malloc(sizeof(struct Item));
  if (item == NULL) {
    struct Error *error =
        create_error("Could not allocate memory for item during it's creation");
    log_error(error);
    return NULL;
  }

  item->ID = ID;
  item->quantity = quantity;
  item->price = price;

  item->name = strdup(name);
  if (item->name == NULL) {
    free(item);
    struct Error *error = create_error(
        "Could not allocate memory for item name during it's creation");
    log_error(error);
    return NULL;
  }

  item->description = strdup(description);
  if (item->description == NULL) {
    struct Error *error = create_error(
        "Could not allocate memory for item description during it's creation");
    log_error(error);
    free(item->name);
    free(item);
    return NULL;
  }

  return item;
}
char *delete_item(struct Item *item) {
  if (item == NULL) {
    struct Error *error =
        create_error("Could not delete item because it was NULL");
    log_error(error);
    return NULL;
  } else {
    free(item->name);
    free(item->description);
    free(item);
    return NULL;
  }
}

void print_item(struct Item *item) {
  printf("Item ID: %d\n", item->ID);
  printf("Quantity: %d\n", item->quantity);
  printf("Price: %.2f\n", item->price);
  printf("Name: %s\n", item->name);
  printf("Description: %s\n", item->description);
}

int get_max_length(struct Item *item) {
  int max_length = 0;

  char id_str[32];
  int id_len = snprintf(id_str, sizeof(id_str), "%d", item->ID);
  if (id_len > max_length) {
    max_length = id_len;
  }

  char quantity_str[32];
  int quantity_len =
      snprintf(quantity_str, sizeof(quantity_str), "%d", item->quantity);
  if (quantity_len > max_length) {
    max_length = quantity_len;
  }

  char price_str[32];
  int price_len = snprintf(price_str, sizeof(price_str), "%.3f", item->price);
  if (price_len > max_length) {
    max_length = price_len;
  }
  if (strlen(item->name) > max_length) {
    max_length = strlen(item->name);
  }
  return max_length;
}

void print_formatted_field(const char *label, const char *value, int max_width,
                           const char *cyan, const char *reset) {
  int spaces = max_width - strlen(label) - strlen(value);
  printf("%s%s%s", cyan, label, reset);
  for (int i = 0; i < spaces; i++) {
    printf(" ");
  }
  printf("%s\n", value);
}

void print_wrapped_description(const char *description, int max_width,
                               const char *indent) {

  if (strlen(description) <= max_width) {
    print_formatted_field("Description:", description, max_width, ACCENT,
                          RESET);
    return;
  }

  printf("%sDescription: %s\n", ACCENT, RESET);
  char description_line[max_width];
  char *description_copy = strdup(description);
  char *word = strtok(description_copy, " ");
  int current_line_len = 0;

  if (word != NULL) {
    strcpy(description_line, word);
    current_line_len = strlen(word);
    word = strtok(NULL, " ");

    while (word != NULL) {
      if (current_line_len + strlen(word) + 1 <= max_width - strlen(indent)) {
        strcat(description_line, " ");
        strcat(description_line, word);
        current_line_len += strlen(word) + 1;
      } else {
        printf("%s%s\n", indent, description_line);
        strcpy(description_line, word);
        current_line_len = strlen(word);
      }
      word = strtok(NULL, " ");
    }
    printf("%s%s\n", indent, description_line);
  }

  free(description_copy);
}

char get_operation() {
  char msg[100];
  sprintf(msg, "[%sA%s]ccept   [%sE%s]dit   [%sD%s]elete", ACCENT, RESET,
          ACCENT, RESET, ACCENT, RESET);
  print_bottom_message(msg);

  char input = getch();
  clear_screen();
  return input;
}

void show_item(struct Item *item) {
  const char SPACING = 16;
  const int MAX_WIDTH = 11 + SPACING + get_max_length(item);

  char id_str[20], price_str[20], quantity_str[20];
  sprintf(id_str, "%d", item->ID);
  sprintf(price_str, "%.2f", item->price);
  sprintf(quantity_str, "%d", item->quantity);

  int id_len = strlen(id_str);
  int remaining_width = MAX_WIDTH / 2 - id_len;
  int left_side = remaining_width / 2;
  int right_side = remaining_width - left_side;

  printf("%s", ACCENT);
  for (int i = 0; i < left_side; i++)
    printf("%s==", RESET);
  printf(" %s%s ", ACCENT, id_str);
  for (int i = 0; i < right_side; i++)
    printf("%s==", RESET);

  printf("%s\n", RESET);
  print_formatted_field("Name:", item->name, MAX_WIDTH, ACCENT, RESET);
  print_formatted_field("Price:", price_str, MAX_WIDTH, ACCENT, RESET);
  print_formatted_field("Quantity:", quantity_str, MAX_WIDTH, ACCENT, RESET);

  print_wrapped_description(item->description, MAX_WIDTH, "  ");

  for (int i = 0; i < MAX_WIDTH / 2; i++)
    printf("==");
}

struct Item *get_user_input_for_item() {
  int ID, quantity;
  float price;
  char name[50];
  char description[100];
  clear_screen();
  move_cursor(1, 1);
  printf("Enter Item ID: ");
  scanf("%d", &ID);
  printf("Enter Item Quantity: ");
  scanf("%d", &quantity);
  printf("Enter Item Price: ");
  scanf("%f", &price);
  printf("Enter Item Name: ");
  getchar();
  // Clear the newline left by previous input
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = 0;
  printf("Enter Item Description: ");
  fgets(description, sizeof(description), stdin);
  description[strcspn(description, "\n")] =
      0; // Remove the newline character // Create and return the new item
  struct Item *new_item = create_item(ID, quantity, price, name, description);
  show_item(new_item);

  char op = get_operation();
  switch (op) {
  case 'a':
    print_message(
        "Item added successfully, with id = %d, quantity = %d, name = %s, "
        "description,  %s, price = %.2f   and ID = %d, lorem ipsum dolor sit "
        "amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt "
        "ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis "
        "nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo "
        "consequat. Duis aute irure dolor in reprehenderit in voluptate velit "
        "esse ci");
    return new_item;
  case 'e':
    printf("Edit");
    return new_item;
  case 'd':
    printf("Delete");
    return new_item;
  default:
    return new_item;
  }
  return new_item;
}
