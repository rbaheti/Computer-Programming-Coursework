#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"

Book Book::operator+=(const int quantityOfBooks) {
  quantityOnHand += quantityOfBooks;
  return *this;
}

Book Book::operator-=(const int quantityOfBooks) {
  quantityOnHand -= quantityOfBooks;
  return *this;
}