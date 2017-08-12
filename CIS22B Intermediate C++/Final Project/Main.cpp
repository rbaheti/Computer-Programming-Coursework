#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"
#include "Inventory.h"
#include "Cashier.h"
#include "Report.h"
#include "ReportByAge.h"
#include "ReportByCost.h"
#include "ReportByQuantity.h"
using namespace std;

// Function prototypes:
void CashierMenu();
void InventoryMenu();
void SearchChoice();
void AddChoice();
void EditBookChoice();
void DeleteBookChoice();
void ReportMenu();
// Make Inventory object global so that it can be accessed by Casier and Report classes.
Inventory inventory;

// ReadIntegerInput() method is used to read integer input from the user.
// When an invalid input is entered, this method will throw an exception until a valid number is enterd.
int ReadIntegerInput(int startValue, int endValue) {
  string choice;
  cin >> choice;
  cin.ignore(9999999999999, '\n');

  // atoi returns 0 when the conversion of string to integer is not possible due to invalid input.
  int intChoice = atoi(choice.c_str());
  if (intChoice < startValue || intChoice > endValue) {
    throw "Invalid entry. Please try again.\n";
  }
  return intChoice;
}

// ValidateDate() method is used to validate the date given by the user.
// When an invalid date is entered, this method will throw an exception until a valid date is enterd.
void ValidateDate(string date) {
  if (date.size() != 10) {
    throw "Invalid entry. Please enter date in MM/DD/YYYY format.\n";
  }

  bool valid = true;
  for (int i = 0; i < date.size(); ++i) {
    char ch = date.at(i);
    if (i == 2 || i == 5) {
      if (ch != '/') {
        valid = false;
        break;
      }
    }
    else if (!isdigit(ch)) {
      valid = false;
      break;
    }
  }

  if (!valid) {
    throw "Invalid entry. Please enter date in MM/DD/YYYY format.\n";
  }

  // Get month from the date.
  string strMonth = date.substr(0, 2);
  // Convert string to int.
  int month = atoi(strMonth.c_str());
  if (month < 1 || month > 12) {
    valid = false;
  }

  // Get day from the date.
  string strDay = date.substr(3, 2);
  // Convert string to int.
  int day = atoi(strDay.c_str());
  if (day < 1 || day > 31) {
    valid = false;
  }

  // Get year from the date.
  string strYear = date.substr(6, 4);
  // Convert string to int.
  int year = atoi(strYear.c_str());
  if (year < 0) {
    valid = false;
  }

  if (!valid) {
    throw "Invalid entry. Please enter date in MM/DD/YYYY format.\n";
  }
}

int main() {
  // Read books from the file.
  inventory.ReadInventoryFromFile();
  while (1) {
    cout << endl;
    cout << "_________________________________" << endl << endl;
    cout << "   Serendipity Booksellers " << endl;
    cout << "          Main Menu " << endl << endl;
    cout << "1. Cashier Module " << endl;
    cout << "2. Inventory Database Module " << endl;
    cout << "3. Report Module " << endl;
    cout << "4. Exit " << endl;
    cout << "_________________________________" << endl << endl;

    bool tryAgain = true;
    int choice = 0;
    while (tryAgain) {
      try {
        cout << "Enter your choice: ";
        choice = ReadIntegerInput(1, 4);
        tryAgain = false;
      }
      catch (char *exceptionString) {
        cout << exceptionString;
      }
    }

    if (choice == 1) {
      CashierMenu();
    }

    else if (choice == 2) {
      InventoryMenu();
    }

    else if (choice == 3) {
      ReportMenu();
    }
    else if (choice == 4) {
      cout << "Good Bye!";
      break;
    }
  }

  // Write all the books back to the Inventory.txt file.
  inventory.WriteInventoryToFile();

  cin.get();
  cin.get();
  return 0;
}

void CashierMenu() {
  Cashier cashier(&inventory);
  int choice = 1;
  while (choice != 4) {
    cout << endl;
    cout << "_________________________________" << endl << endl;
    cout << "   Serendipity Booksellers " << endl;
    cout << "       Cashier Menu " << endl << endl;
    cout << "1. Add Book to the Sale" << endl;
    cout << "2. Look Up a Book (to find its ISBN)" << endl;
    cout << "3. Print Bill " << endl;
    cout << "4. Return to the Main Menu " << endl;
    cout << "_________________________________" << endl << endl;

    bool tryAgain = true;
    while (tryAgain) {
      try {
        cout << "Enter your choice: ";
        choice = ReadIntegerInput(1, 4);
        tryAgain = false;
      }
      catch (char *exceptionString) {
        cout << exceptionString;
      }
    }

    switch (choice) {
    case 1: {
      int quantity = 0;
      Book book;
      cout << "Please enter the ISBN of the book you want to purchase: ";
      getline(cin, book.ISBN);

      bool tryAgain = true;
      while (tryAgain) {
        try {
          cout << "Please enter the quantity of the book you want to purchase: ";
          quantity = ReadIntegerInput(1, INT_MAX);
          tryAgain = false;
        }
        catch (char *exceptionString) {
          cout << exceptionString;
        }
      }

      bool sell_book_status = cashier.SellBook(book.ISBN, quantity);
      if (sell_book_status) {
        cout << "Your book has been added to the cart." << endl << endl;
      }
      break;
    }

    case 2: {
      SearchChoice();
      break;
    }

    case 3: {
      cashier.PrintBill();
      break;
    }

    case 4:
      cout << "Returning to the main menu.." << endl << endl;
      break;

    default:
      cout << "Invalid Entry. Please try again." << endl;
    }
  }
}

void InventoryMenu() {
  int choice = 1;
  while (choice != 5) {
    cout << endl;
    cout << "_________________________________" << endl << endl;
    cout << "   Serendipity Booksellers " << endl;
    cout << "     Inventory Database " << endl << endl;
    cout << "1. Look Up a Book" << endl;
    cout << "2. Add a Book" << endl;
    cout << "3. Edit a Book's Record" << endl;
    cout << "4. Delete a Book" << endl;
    cout << "5. Return to the Main Menu" << endl;
    cout << "_________________________________" << endl << endl;

    bool tryAgain = true;
    while (tryAgain) {
      try {
        cout << "Enter your choice: ";
        choice = ReadIntegerInput(1, 5);
        tryAgain = false;
      }
      catch (char *exceptionString) {
        cout << exceptionString;
      }
    }

    switch (choice) {
    case 1:
      SearchChoice();
      break;

    case 2:
      AddChoice();
      break;

    case 3:
      EditBookChoice();
      break;

    case 4:
      DeleteBookChoice();

    case 5:
      cout << "Returning to the main menu.." << endl << endl;
      break;

    default:
      cout << "Invalid Entry. Please try again." << endl << endl;
    }
  }
}

void SearchChoice() {
  int search_choice = 1;
  Book book_search;
  string line;
  int index = -1;

  cout << "How would you like to look up the book?" << endl << endl;

  while (search_choice > 0) {
    cout << "1. Look up by ISBN" << endl;
    cout << "2. Look up by Title" << endl;
    cout << "3. Look up by Author" << endl;
    cout << "4. Look up by Publisher" << endl << endl;

    bool tryAgain = true;
    while (tryAgain) {
      try {
        cout << "Enter your choice: ";
        search_choice = ReadIntegerInput(1, 4);
        tryAgain = false;
      }
      catch (char *exceptionString) {
        cout << exceptionString;
      }
    }

    if (search_choice == 1) {
      cout << "Please enter the ISBN: ";
      getline(cin, book_search.ISBN);
      inventory.PrintAllSimilarSearchedBooks(book_search, true, false, false, false);
    }
    else if (search_choice == 2) {
      cout << "Please enter the Title: ";
      getline(cin, book_search.title);
      inventory.PrintAllSimilarSearchedBooks(book_search, false, true, false, false);
    }
    else if (search_choice == 3) {
      cout << "Please enter the Author: ";
      getline(cin, book_search.author);
      inventory.PrintAllSimilarSearchedBooks(book_search, false, false, true, false);
    }
    else if (search_choice == 4) {
      cout << "Please enter Publisher of the book: ";
      getline(cin, book_search.publisher);
      inventory.PrintAllSimilarSearchedBooks(book_search, false, false, false, true);
    }

    string contdSearch;
    cout << "Do you want to search more books? Y/N?" << endl;
    cout << "Press 'Y' for yes, 'N' to exit: ";
    getline(cin, contdSearch);
    if (contdSearch == "y" || contdSearch == "Y") {
      continue;
    }
    else {
      break;
    }
  }
}

void AddChoice() {
  Book book_to_add;
  int quantity = 0;
  while (1) {
    cout << "Please enter ISBN and Quantity of the book to be added." << endl;
    cout << "ISBN: ";
    getline(cin, book_to_add.ISBN);
    cout << "Quantity: ";
    cin >> quantity;
    // Read and discard the new line character.
    cin.get();

    int found_index = inventory.SearchBookByISBN(book_to_add.ISBN);
    if (found_index != -1) {
      inventory.AddBook(book_to_add, quantity);
      cout << "Your book has been added to the inventory." << endl << endl;
    }
    else {
      cout << "Please give more information to add your book to the database." << endl;
      cout << "Please enter Title: ";
      getline(cin, book_to_add.title);
      cout << "Please enter Author: ";
      getline(cin, book_to_add.author);
      cout << "Please enter Publisher: ";
      getline(cin, book_to_add.publisher);

      bool tryAgain = true;
      while (tryAgain) {
        try {
          cout << "Please enter Today's Date: ";
          getline(cin, book_to_add.dateAdded);
          ValidateDate(book_to_add.dateAdded);
          tryAgain = false;
        }
        catch (char *exceptionString) {
          cout << exceptionString;
        }
      }

      cout << "Please enter Wholesale Cost: ";
      cin >> book_to_add.wholeSaleCost;
      cout << "Please enter Retail Price: ";
      cin >> book_to_add.retailCost;
      cout << "Adding this book:\n";
      inventory.AddBook(book_to_add, quantity);
      cout << "Your book has been added to the inventory." << endl << endl;
    }

    string contdAdd;
    cout << "Do you want to add more books? Y/N?" << endl;
    cout << "Press 'Y' for yes, 'N' to exit: ";
    getline(cin, contdAdd);
    if (contdAdd == "y" || contdAdd == "Y") {
      continue;
    }
    else {
      break;
    }
  }
}

void EditBookChoice() {
  while (1) {
    Book book_new_detail;
    int modify_choice = 1;
    cout << "Please enter the ISBN of the book you want to modify: ";
    getline(cin, book_new_detail.ISBN);
    int index = inventory.SearchBookByISBN(book_new_detail.ISBN);
    if (index == -1) {
      string contdEdit;
      cout << "Do you want to edit more books? Y/N?" << endl;
      cout << "Press 'Y' for yes, 'N' to exit: ";
      getline(cin, contdEdit);
      if (contdEdit == "y" || contdEdit == "Y") {
        continue;
      }
      else {
        break;
      }
    }
    else {
      cout << "Your current book details are: " << endl;
      inventory.PrintOneBook(index);
      cout << "What do you want to modify?" << endl;
      cout << "1. ISBN " << endl;
      cout << "2. Title " << endl;
      cout << "3. Author " << endl;
      cout << "4. Publisher " << endl;
      cout << "5. Date Added " << endl;
      cout << "6. Quantity on Hand " << endl;
      cout << "7. Wholesale Cost " << endl;
      cout << "8. Retail Price " << endl;
      cout << "9. Go to the previous menu " << endl << endl;
      cout << "Please enter your choice: ";

      bool tryAgain = true;
      while (tryAgain) {
        try {
          cout << "Enter your choice: ";
          modify_choice = ReadIntegerInput(1, 9);
          tryAgain = false;
        }
        catch (char *exceptionString) {
          cout << exceptionString;
        }
      }

      if (modify_choice == 1) {
        cout << "Please enter new ISBN: ";
        getline(cin, book_new_detail.ISBN);
        inventory.ChangeBookDetail(index, book_new_detail, true, false, false,
          false, false, false, false, false);
        cout << "Your book's ISBN has been modified." << endl;
      }
      else if (modify_choice == 2) {
        cout << "Please enter new Title: ";
        getline(cin, book_new_detail.title);
        inventory.ChangeBookDetail(index, book_new_detail, false, true, false,
          false, false, false, false, false);
        cout << "Your book's title has been modified." << endl;
      }
      else if (modify_choice == 3) {
        cout << "Please enter new Author: ";
        getline(cin, book_new_detail.author);
        inventory.ChangeBookDetail(index, book_new_detail, false, false, true,
          false, false, false, false, false);
        cout << "Your book's Author name has been modified." << endl;
      }
      else if (modify_choice == 4) {
        cout << "Please enter new Publisher: ";
        getline(cin, book_new_detail.publisher);
        inventory.ChangeBookDetail(index, book_new_detail, false, false, false,
          true, false, false, false, false);
        cout << "Your book's Publisher has been modified." << endl;
      }
      else if (modify_choice == 5) {
        bool tryAgain = true;
        while (tryAgain) {
          try {
            cout << "Please enter new Date: ";
            getline(cin, book_new_detail.dateAdded);
            ValidateDate(book_new_detail.dateAdded);
            tryAgain = false;
          }
          catch (char *exceptionString) {
            cout << exceptionString;
          }
        }

        inventory.ChangeBookDetail(index, book_new_detail, false, false, false,
          false, true, false, false, false);
        cout << "Your book's date has been modified." << endl;
      }
      else if (modify_choice == 6) {
        cout << "Please enter new Quantity on hand: ";
        cin >> book_new_detail.quantityOnHand;
        inventory.ChangeBookDetail(index, book_new_detail, false, false, false,
          false, false, true, false, false);
        cout << "Your book's quantity has been modified." << endl;
      }
      else if (modify_choice == 7) {
        cout << "Please enter new Wholesale Cost: ";
        cin >> book_new_detail.wholeSaleCost;
        inventory.ChangeBookDetail(index, book_new_detail, false, false, false,
          false, false, false, true, false);
        cout << "Your book's wholesale cost has been modified." << endl;
      }
      else if (modify_choice == 8) {
        cout << "Please enter new Retail Price: ";
        cin >> book_new_detail.retailCost;
        inventory.ChangeBookDetail(index, book_new_detail, false, false, false,
          false, false, false, false, true);
        cout << "Your book's retail price has been modified." << endl;
      }
      else if (modify_choice == 9) {
        cout << "Returning to the previous menu.." << endl << endl;
        break;
      }
      else {
        cout << "Invalid Entry. Please try again." << endl;
      }
    }
    string contdEdit;
    cout << "Do you want to edit more books? Y/N?" << endl;
    cout << "Press 'Y' for yes, 'N' to exit: ";
    getline(cin, contdEdit);
    if (contdEdit == "y" || contdEdit == "Y") {
      continue;
    }
    else {
      break;
    }
  }
}

void DeleteBookChoice() {
  while (1) {
    Book book_remove;
    string ISBN;
    bool status = false;
    cout << "Please enter the ISBN of the book you want to delete: ";
    getline(cin, ISBN);
    inventory.RemoveBook(ISBN);
    string contdDelete;
    cout << "Do you want to delete more books? Y/N?" << endl;
    cout << "Press 'Y' for yes, 'N' to exit: ";
    getline(cin, contdDelete);
    if (contdDelete == "y" || contdDelete == "Y") {
      continue;
    }
    else {
      break;
    }
  }
}

void ReportMenu() {
  Report *report = NULL;
  int choice = 1;
  while (choice != 7) {
    cout << endl;
    cout << "_________________________________" << endl << endl;
    cout << "   Serendipity Booksellers " << endl;
    cout << "          Reports  " << endl << endl;
    cout << "1. Inventory Listing" << endl;
    cout << "2. Inventory Wholesale Value" << endl;
    cout << "3. Inventory Retail Value" << endl;
    cout << "4. Listing by Quantity" << endl;
    cout << "5. Listing by Cost" << endl;
    cout << "6. Listing by Age" << endl;
    cout << "7. Return to the Main Menu" << endl;
    cout << "_________________________________" << endl << endl;

    bool tryAgain = true;
    while (tryAgain) {
      try {
        cout << "Enter your choice: ";
        choice = ReadIntegerInput(1, 7);
        tryAgain = false;
      }
      catch (char *exceptionString) {
        cout << exceptionString;
      }
    }

    switch (choice) {
    case 1:
      // Dynamically create an object of Report class to print Inventory file using polymorphism.
      report = new Report(&inventory);
      report->Print();
      break;

    case 2:
      // Dynamically create an object of Report class to print Wholesale value using polymorphism.
      report = new Report(&inventory);
      report->PrintWholesaleValue();
      break;

    case 3:
      // Dynamically create an object of Report class to print Retail value using polymorphism.
      report = new Report(&inventory);
      report->PrintRetailValue();
      break;

    case 4:
      // Dynamically create an object of Report class to print Quantity of the books in sorted form
      // using polymorphism.
      report = new ReportByQuantity(&inventory);
      report->Print();
      break;

    case 5:
      // Dynamically create an object of Report class to print Wholesale cost of the books in sorted form
      // using polymorphism.
      report = new ReportByCost(&inventory);
      report->Print();
      break;

    case 6:
      // Dynamically create an object of Report class to print Age of the books in sorted form
      // using polymorphism.
      report = new ReportByAge(&inventory);
      report->Print();
      break;

    case 7:
      cout << "Returning to the main menu.." << endl << endl;
      break;

    default:
      cout << "Invalid Entry. Please try again." << endl << endl;
    }
    delete report;
    // Reset report to NULL after deletion.
    report = NULL;
  }
}

