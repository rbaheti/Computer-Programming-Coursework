#define _CRT_SECURE_NO_WARNINGS
#include "ReportByCost.h"

// Call the constructor of base class Report and initialise the list.
ReportByCost::ReportByCost(Inventory *inventory_object) : Report(inventory_object) {
}

void ReportByCost::Print() {
  vector<Book> books_vec = inventory->GetBookVector();
  Book book;
  int minIndex = 0;
  double minValue = 0.0;
  for (int i = 0; i < books_vec.size() - 1; ++i) {
    book = books_vec[i];
    minValue = book.wholeSaleCost;
    minIndex = i;
    for (int j = i + 1; j < books_vec.size(); ++j) {
      book = books_vec[j];
      if (book.wholeSaleCost > minValue) {
        minValue = book.wholeSaleCost;
        minIndex = j;
      }
    }
    Book temp = books_vec[minIndex];
    books_vec[minIndex] = books_vec[i];
    books_vec[i] = temp;
  }
  for (int i = 0; i < books_vec.size(); ++i) {
    book = books_vec[i];
    cout << "Title: " << book.title << endl;
    cout << "Quantity: " << book.wholeSaleCost << endl << endl;
  }
}