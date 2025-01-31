
#include "../inventory/inventory.h"
#include "../memo/memo.h"
#include "../supplier/supplier.h"

int gen_inventory_item(Memo *memo) {
  append_item(memo->inventory,
              *new_inventory_item(0, "Smartphone", 1400.0, 0, 30, 1));
  append_item(memo->inventory,
              *new_inventory_item(0, "Laptop", 1000.0, 2, 40, 3));
  append_item(memo->inventory,
              *new_inventory_item(0, "Keyboard", 500.0, 0, 15, 2));
  append_item(memo->inventory,
              *new_inventory_item(0, "Mouse", 250.0, 1, 20, 1));
  append_item(memo->inventory,
              *new_inventory_item(0, "Headphones", 700.0, 0, 25, 2));
  append_item(memo->inventory,
              *new_inventory_item(0, "Microphone", 800.0, 0, 10, 3));
  append_item(memo->inventory,
              *new_inventory_item(0, "Speakers", 600.0, 3, 35, 1));
  append_item(memo->inventory,
              *new_inventory_item(0, "Headset", 900.0, 0, 25, 2));
  append_item(memo->inventory,
              *new_inventory_item(0, "Camera", 300.0, 1, 15, 3));
  append_item(memo->inventory,
              *new_inventory_item(0, "Monitor", 1500.0, 0, 20, 1));
  return 0;
}

int gen_supplier(Memo *memo) {
  append_supplier(memo->suppliers, *new_supplier(0, "John", "Snow",
                                                 "John@snow.com", "02394234"));
  append_supplier(memo->suppliers, *new_supplier(0, "Kendrick", "Lamar",
                                                 "ken@lamar.com", "02394234"));
  append_supplier(
      memo->suppliers,
      *new_supplier(0, "Michael", "Jordan", "michael@jordan.com", "02394234"));
  return 0;
}

int gen_fake_data(Memo *memo) {
  gen_inventory_item(memo);
  gen_supplier(memo);
  return 0;
}
