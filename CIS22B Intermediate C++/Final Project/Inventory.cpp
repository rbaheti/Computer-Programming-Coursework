#define _CRT_SECURE_NO_WARNINGS
#include "Inventory.h"
#include <fstream>
#include <iostream>
using namespace std;

void Inventory::ReadInventoryFromFile() {
  ifstream inDataFile;
  inDataFile.open("Inventory.txt");
  if (!inDataFile) {
    cout << "File open failure!" << endl << endl;
    return;
  }
  Book book;
  char line[200];

  // Clear the existing books, if any, from the vector.
  books_vec.clear();

  // Read all books from the file until end of the file.
  while (!inDataFile.eof()) {
    inDataFile >> book.ISBN;
    // Read and discard the new line character.
    inDataFile.get();

    inDataFile.getline(line, 200);
    book.title = line;

    inDataFile.getline(line, 200);
    book.author = line;

    inDataFile.getline(line, 200);
    book.publisher = line;

    inDataFile.getline(line, 200);
    book.dateAdded = line;

    inDataFile >> book.quantityOnHand;

    inDataFile >> book.wholeSaleCost;

    inDataFile >> book.retailCost;

    // Populate vector books_vec.
    books_vec.push_back(book);
  }
  inDataFile.close();
}

void Inventory::WriteInventoryToFile() {
  ofstream outDataFile;
  outDataFile.open("Inventory.txt");
  if (!outDataFile) {
    cout << "File open failure!" << endl << endl;
    return;
  }
  for (int i = 0; i < books_vec.size(); ++i) {
    // Write details of ith book to file.
    Book book = books_vec[i];
    outDataFile << book.ISBN << endl;
    outDataFile << book.title << endl;
    outDataFile << book.author << endl;
    outDataFile << book.publisher << endl;
    outDataFile << book.dateAdded << endl;
    outDataFile << book.quantityOnHand << endl;
    outDataFile << book.wholeSaleCost << endl;
    outDataFile << book.retailCost;

    // Dont print an end of line character after the last line in the file
    if (i < books_vec.size() - 1) {
      outDataFile << endl;
    }
  }
  outDataFile.close();
}

int Inventory::SearchBookByISBN(string ISBN_search) {
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];

    if (ISBN_search == book.ISBN) {
      if (book.quantityOnHand > 0) {
        cout << "Your book is available. " << endl;
        return i;
      }
    }
  }
  cout << "Sorry, your book is not available in our database." << endl << endl;
  return -1;
}

void Inventory::PrintAllSimilarSearchedBooks(Book book_search, bool search_by_ISBN,
  bool search_by_title, bool search_by_author,
  bool search_by_publisher) {
  bool found = false;
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];

    if (search_by_ISBN) {
      if (book_search.ISBN == book.ISBN) {
        if (book.quantityOnHand > 0) {
          PrintOneBook(i);
          found = true;
        }
      }
    }

    else if (search_by_title) {
      if (book_search.title == book.title) {
        if (book.quantityOnHand > 0) {
          PrintOneBook(i);
          found = true;
        }
      }
    }

    else if (search_by_author) {
      if (book_search.author == book.author) {
        if (book.quantityOnHand > 0) {
          PrintOneBook(i);
          found = true;
        }
      }
    }

    else if (search_by_publisher) {
      if (book_search.publisher == book.publisher) {
        if (book.quantityOnHand > 0) {
          PrintOneBook(i);
          found = true;
        }
      }
    }
  }
  if (!found) {
    cout << "Sorry, your book is not available in our database." << endl << endl;
  }
}

bool Inventory::RemoveBook(string ISBN) {
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];
    if (ISBN == book.ISBN) {
      books_vec.erase(books_vec.begin() + i);
      cout << "Your book of ISBN \"" << ISBN << "\" has been removed." << endl << endl;
      return true;
    }
  }
  cout << "No such book found to remove." << endl << endl;
  return false;
}

void Inventory::AddBook(Book book_to_add, int quantity) {
  // Add "book_to_add" in the inventory (if the book is already available) 
  // using "book_to_add" ISBN in the SearchBook() function.
  int found_index = SearchBookByISBN(book_to_add.ISBN);
  if (found_index != -1) {
    // Use overloaded += operator to increase the quantity of the book.
    books_vec[found_index] += quantity;
  }
  // If the book is not found in the inventory then add it to the books_vec vector.
  else {
    book_to_add.quantityOnHand = quantity;
    books_vec.push_back(book_to_add);
  }
}

// Here "index" is the location number of the book in the vector books_vec.
void Inventory::ChangeBookDetail(int index, Book book_new_detail,
  bool change_ISBN, bool change_title,
  bool change_author, bool change_publisher,
  bool change_dateAdded, bool change_quantityOnHand,
  bool change_wholeSaleCost, bool change_retailCost) {
  // Modify the book using pointer so that the modifications 
  // are reflected in the book stored in the vector.
  Book *book = &books_vec[index];
  if (change_ISBN) {
    book->ISBN = book_new_detail.ISBN;
  }
  else if (change_title) {
    book->title = book_new_detail.title;
  }
  else if (change_author) {
    book->author = book_new_detail.author;
  }
  else if (change_publisher) {
    book->publisher = book_new_detail.publisher;
  }
  else if (change_dateAdded) {
    book->dateAdded = book_new_detail.dateAdded;
  }
  else if (change_quantityOnHand) {
    book->quantityOnHand = book_new_detail.quantityOnHand;
  }
  else if (change_wholeSaleCost) {
    book->wholeSaleCost = book_new_detail.wholeSaleCost;
  }
  else if (change_retailCost) {
    book->retailCost = book_new_detail.retailCost;
  }
}

// Print all books' information on console.
void Inventory::PrintAllBooks() {
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];
    PrintOneBook(book);
  }
}

// Print book information (one book at a time)
void Inventory::PrintOneBook(Book book_print) {
  cout << "   Serendipity Boolsellers " << endl;
  cout << "       Book Information " << endl << endl;
  cout << "ISBN: " << book_print.ISBN << endl;
  cout << "Title: " << book_print.title << endl;
  cout << "Author: " << book_print.author << endl;
  cout << "Publisher: " << book_print.publisher << endl;
  cout << "Date Added: " << book_print.dateAdded << endl;
  cout << "Quantity on hand: " << book_print.quantityOnHand << endl;
  cout << "Wholesale cost: " << book_print.wholeSaleCost << endl;
  cout << "Retail cost: " << book_print.retailCost << endl << endl;
}

// Return book at index i to the function PrintOneBook(Book).
void Inventory::PrintOneBook(int index) {
  Book book_print = books_vec[index];
  PrintOneBook(book_print);
}

// Reduce the book quantity when the book is bought.
bool Inventory::ReduceBookQuantity(int quantity, int index) {
  Book *sell_book = &books_vec[index];
  if (sell_book->quantityOnHand >= quantity) {
    // Use overloaded -= operator to increase the quantity of the book.
    *sell_book -= quantity;

    // Remove book from the books_vec vector if the quantity is 0.
    if (sell_book->quantityOnHand == 0) {
      books_vec.erase(books_vec.begin() + index);
    }
    return true;
  }
  cout << "Sorry, you cannot checkout more than " << sell_book->quantityOnHand
    << " units of this book." << endl;
  return false;
}

Book Inventory::GetBook(int index) {
  Book book = books_vec[index];
  return book;
}

vector<Book> Inventory::GetBookVector() {
  return books_vec;
}