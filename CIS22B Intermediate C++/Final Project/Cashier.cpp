#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include "Cashier.h"
using namespace std;

// Pass inventory_object's pointer to the Cashier constructor
// and set it to the "inventory" variable so that it can be used 
// throughout the Cashier class.
// Pass it as a pointer variable so that the inventory object used in Cashier class 
// is same as the inventory object used in Inventory class. 
Cashier::Cashier(Inventory *inventory_object) {
  inventory = inventory_object;
}

bool Cashier::SellBook(string ISBN, int quantity) {
  int index = inventory->SearchBookByISBN(ISBN);
  if (index != -1) {
    Book book = inventory->GetBook(index);
    bool book_reduce_status = inventory->ReduceBookQuantity(quantity, index);
    if (book_reduce_status) {
      // Add book to sold_books_vec and update its quantityOnHand as necessary.
      bool already_sold = false;
      for (int i = 0; i < sold_books_vec.size(); ++i) {
        if (sold_books_vec[i].ISBN == ISBN) {
          // The book was already sold, increase its quantityOnHand by quantity.
          sold_books_vec[i].quantityOnHand += quantity;
          already_sold = true;
          break;
        }
      }
      if (!already_sold) {
        // The book is not already sold, set its quantityOnHand to quantity.
        book.quantityOnHand = quantity;
        sold_books_vec.push_back(book);
      }
      totalCost += book.retailCost * quantity;
    }
    return book_reduce_status;
  }
  return false;
}

void Cashier::PrintBill() {
  // Get today's date.
  char date[9];
  _strdate(date);
  time_t now = time(0);

  cout << endl;
  cout << "_____________________________________________________________________" << endl;
  cout << "Serendipity BookSellers" << endl << endl;
  cout << "Date: " << date << endl;
  // Display the header
  cout << setw(5) << left << "Qty" << setw(20) << "ISBN" << setw(30) << "Title"
    << setw(8) << "Price" << setw(8) << "Total" << endl;
  cout << "_____________________________________________________________________" << endl;
  // Display the book bought list
  for (int i = 0; i < sold_books_vec.size(); i++)
  {
    cout << setw(5) << left << sold_books_vec[i].quantityOnHand
      << setw(20) << sold_books_vec[i].ISBN.substr(0, 15)
      << setw(30) << sold_books_vec[i].title.substr(0, 28)
      << setw(8) << sold_books_vec[i].retailCost
      << setw(8) << sold_books_vec[i].retailCost * sold_books_vec[i].quantityOnHand << endl;
  }
  cout << endl;
  // Display the subtotal
  cout << setw(20) << "                 " << setw(15) << "Subtotal: " << setw(2) << "$" << setw(15) << fixed << setprecision(2) << totalCost << endl;
  // Calculate the tax
  cout << setw(20) << "                 " << setw(15) << "Tax: " << setw(2) << "$" << setw(15) << fixed << setprecision(2) << tax * totalCost << endl;

  //display the total 
  double total = tax * totalCost + totalCost;
  cout << setw(20) << "                 " << setw(15) << "Total: " << setw(2) << "$" << setw(15) << fixed << setprecision(2) << total << endl;
}