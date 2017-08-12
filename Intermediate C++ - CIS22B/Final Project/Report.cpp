#define _CRT_SECURE_NO_WARNINGS
#include "Report.h"
#include "Inventory.h"
using namespace std;

// Pass inventory_object's pointer to the Report constructor
// and set it to the "inventory" variable so that it can be used 
// throughout the Report class.
// Pass it as a pointer variable so that the inventory object used in Report class 
// is same as the inventory object used in Inventory class. 
Report::Report(Inventory *inventory_object) {
  inventory = inventory_object;
}

Report::~Report() {
}

void Report::Print() {
  inventory->PrintAllBooks();
}

void Report::PrintWholesaleValue() {
  vector<Book> books_vec = inventory->GetBookVector();
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];
    cout << "Title: " << book.title << endl;
    cout << "Wholesale Cost: $" << book.wholeSaleCost << endl << endl;
    totalCost += book.wholeSaleCost;
  }
  cout << "Total Wholesale Value of the Inventory is: $" << totalCost << endl << endl;
}

void Report::PrintRetailValue() {
  vector<Book> books_vec = inventory->GetBookVector();
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];
    cout << "Title: " << book.title << endl;
    cout << "Retail Cost: $" << book.retailCost << endl << endl;
    totalCost += book.retailCost;
  }
  cout << "Total Retail Value of the Inventory is: $" << totalCost << endl << endl;
}

