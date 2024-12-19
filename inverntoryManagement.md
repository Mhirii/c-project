# Cahier des Charges

## Project Title
Inventory Management System

## Project Overview
The Inventory Management System is designed to help businesses manage their inventory efficiently. The system will allow users to perform CRUD operations on inventory items, track item quantities, generate inventory reports, manage suppliers, and handle purchase orders. The system will also read configuration settings from a config file to adjust its behavior.

## Objectives
- Develop a command-line interface (CLI) tool for managing inventory.
- Implement CRUD for inventory items.
- Implement CRUD for suppliers.
- Track and alert low stock items.
- Generate detailed inventory reports.
- Manage purchase orders.
- Read and apply settings from a config file.

## Functional Requirements

1. **CRUD Operations for Inventory Items**
   - Add new inventory items with details such as name, ID, quantity, and price.
   - Display a list of all inventory items or search for specific items.
   - Modify details of existing inventory items.
   - Remove inventory items from the system.

2. **Track Item Quantities**
   - Monitor the quantity of each item in stock.
   - Alert when items are low in stock based on predefined reorder levels.

3. **Generate Inventory Reports**
   - Create reports showing current stock levels, low stock items, and inventory value.
   - Generate periodic reports (e.g., weekly, monthly) for inventory analysis.

4. **Read Config File for Settings**
   - Load settings from a config file, such as reorder levels, supplier details, and report generation frequency.
   - Adjust system behavior based on config file parameters.

5. **Supplier Management**
   - Store and manage supplier information.
   - Link inventory items to their respective suppliers.

6. **Order Management**
   - Create and manage purchase orders for restocking items.
   - Track order status and update inventory upon order receipt.

## Non-Functional Requirements
- The tool should handle errors gracefully and provide meaningful error messages.
- The tool should be efficient and perform operations quickly.

## Data Structures

1. **Structs for Inventory Items**
   - Define structures to store inventory item details such as name, ID, quantity, and price.

2. **Structs for Suppliers**
   - Define structures to store supplier details such as name, contact information, and email.

3. **Linked Lists to Store Inventory Items**
   - Use arrays or linked lists to store multiple inventory items.

4. **Linked Lists to Store Suppliers**
   - Use arrays or linked lists to store multiple suppliers.

5. **Config File Handling**
   - Implement file I/O to read settings from a config file.

---

Does this look good to you? 😊
