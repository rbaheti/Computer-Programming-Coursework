#ifndef _CASHIER_H_
#define _CASHIER_H_

#include <vector>
#include "Book.h"
#include "Inventory.h"

class Cashier {
public:

  // Cashier constructor accept pointer to the inventory object, 
  // which is also used in the main function.
  Cashier(Inventory *inventory_object);

  bool SellBook(string ISBN, int quantity);

  void PrintBill();

private:
  Inventory *inventory;

  // This vector stores all the information of all the sold books.
  vector<Book> sold_books_vec;
  
  double totalCost = 0;
  const double tax = 0.10;
};

#endif
