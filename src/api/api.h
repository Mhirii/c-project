
#ifndef API_H
#define API_H

#include "../memo/memo.h"

int add_inv_item(Memo* memo);
int del_inv_item(Memo* memo);
int update_inv_item(Memo* memo);
int list_inv_items(Memo* memo);
int search_inv_item_id(Memo* memo);
int search_inv_item_name(Memo* memo);

int add_supp(Memo* memo);
int del_supp(Memo* memo);
int update_supp(Memo* memo);
int list_supp(Memo* memo);
int search_supplier_id(Memo* memo);
int search_supplier_name(Memo* memo);
int list_supplier_items(Memo* memo);


#endif
