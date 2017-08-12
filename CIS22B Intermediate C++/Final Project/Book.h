#ifndef _BOOK_H_
#define _BOOK_H_
#include <string>
using namespace std;

class Book {
public:
  string ISBN;
  string title;
  string author;
  string publisher;
  string dateAdded;
  int quantityOnHand;
  double wholeSaleCost;
  double retailCost;

  // Overload += operator function
  Book operator+=(const int quantityOfBooks);

  // Overload -= operator function
  Book operator-=(const int quantityOfBooks);
};

#endif