#define _CRT_SECURE_NO_WARNINGS
#include "ReportByAge.h"

// Call the constructor of base class Report and initialise the list.
ReportByAge::ReportByAge(Inventory *inventory_object) : Report(inventory_object) {
}

void ReportByAge::Print() {
  vector<Book> books_vec = inventory->GetBookVector();
  for (int i = 0; i < books_vec.size() - 1; ++i) {
    Book book_i = books_vec[i];
    string str = book_i.dateAdded;

    // Get the Year from dateAdded in the inventory.
    string strYear = str.substr(6, 4);
    // Convert string to int.
    int maxYear = atoi(strYear.c_str());

    // Get month from dateAdded in the inventory.
    string strMonth = str.substr(0, 2);
    // Convert string to int.
    int maxMonth = atoi(strMonth.c_str());

    // Get day from dateAdded in the inventory.
    string strDay = str.substr(3, 2);
    // Convert string to int.
    int maxDay = atoi(strDay.c_str());

    int maxIndex = i;

    for (int j = i + 1; j < books_vec.size(); ++j) {
      Book book_j = books_vec[j];
      str = book_j.dateAdded;

      // Get the Year from dateAdded in the inventory.
      strYear = str.substr(6, 4);
      // Convert string to int.
      int year = atoi(strYear.c_str());

      // Get month from dateAdded in the inventory.
      strMonth = str.substr(0, 2);
      // Convert string to int.
      int month = atoi(strMonth.c_str());

      // Get day from dateAdded in the inventory.
      strDay = str.substr(3, 2);
      // Convert string to int.
      int day = atoi(strDay.c_str());

      if (year > maxYear) {
        maxYear = year;
        maxMonth = month;
        maxDay = day;
        maxIndex = j;
      }
      if (month > maxMonth && year == maxYear) {
        maxYear = year;
        maxMonth = month;
        maxDay = day;
        maxIndex = j;
      }
      if (day > maxDay && year == maxYear && month == maxMonth) {
        maxYear = year;
        maxMonth = month;
        maxDay = day;
        maxIndex = j;
      }
    }
    Book temp = books_vec[maxIndex];
    books_vec[maxIndex] = books_vec[i];
    books_vec[i] = temp;
  }
  for (int i = 0; i < books_vec.size(); ++i) {
    Book book = books_vec[i];
    cout << "Title: " << book.title << endl;
    cout << "Date: " << book.dateAdded << endl << endl;
  }
}