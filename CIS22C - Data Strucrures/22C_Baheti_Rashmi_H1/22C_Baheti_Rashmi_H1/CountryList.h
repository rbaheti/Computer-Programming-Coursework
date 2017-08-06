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
  int cnt;         // keeps track of the number of countries in the list

public:
  CountryList();  // Constructor
  ~CountryList(); // Destructor

                  // Basic Linked List Operations
  int getCount() { return cnt; }
  void insertNode(Country);
  int deleteNode(const char*);
  void displayList() const;
  Country* findCountry(const char*);
  Country* findCountryWithLargestPopulation();
};
#endif
