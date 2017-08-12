#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "Book.h"
#include <vector>
using namespace std;

class Inventory {
public:
  // Reads books stored in "Inventory.txt" file and populates vector books_vec.
  void ReadInventoryFromFile();

  // Writes to "Inventory.txt" file.
  void WriteInventoryToFile();

  // Searches a book using given ISBN. Returns the index of the book found.
  int SearchBookByISBN(string ISBN_search);

  // Searches books using book_search.ISBN or book_search.title or
  // book_search.author or book_search.publisher and prints the searched books.
  void PrintAllSimilarSearchedBooks(Book book_search, bool search_by_ISBN,
    bool search_by_title, bool search_by_author,
    bool search_by_publisher);

  // Searches a book using book_search.ISBN or book_search.title or
  // book_search.author or book_search.publisher.
  bool RemoveBook(string ISBN);

  // Adds quantity of books if the book already exists or 
  // appends a new book to the vector books_vec.
  void AddBook(Book book_to_add, int quantity);

  // Modifies book details
  void ChangeBookDetail(int index, Book book_new_detail,
    bool change_ISBN, bool change_title,
    bool change_author, bool change_publisher,
    bool change_dateAdded, bool change_quantityOnHand,
    bool change_wholeSaleCost, bool change_retailCost);

  // Prints all books, present in the vector books_vec, on console. 
  void PrintAllBooks();

  //Print all information of a particular look-up book
   void PrintOneBook(Book book_print);

   void PrintOneBook(int index);

   bool ReduceBookQuantity(int quantity, int index);

   Book GetBook(int index);

private:
  // Make all the Report classes friends of this class so that they can call GetBookVector() method.
  friend class Report;
  friend class ReportByQuantity;
  friend class ReportByCost;
  friend class ReportByAge;

  // Private method, currently used by friends of this class.
  vector<Book> GetBookVector();

  // This vector stores all the information of all the books.
  vector<Book> books_vec;
};

#endif
