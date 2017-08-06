// Specification file for the CountryList class
#ifndef COUNTRYLIST_H
#define COUNTRYLIST_H

#include <iomanip>
#include <string>
#include <cstring>
using namespace std;
#include "Country.h"
#include "ListNode.h"

class CountryList
{
private:
  ListNode *head;  // pointer to the first node in the list
  int count;         // keeps track of the number of countries in the list

public:
  CountryList();  // Constructor
  ~CountryList(); // Destructor

                  // Basic Linked List Operations
  int getCount() { return count; }
  void insertNode(Country);
  int deleteNode(const char*);
  void displayListForward() const;
  void displayListBackward() const;
  Country* findCountry(const char*);
  Country* findCountryWithLargestPopulation();
  void findLetterInString(char letter);
};
#endif
