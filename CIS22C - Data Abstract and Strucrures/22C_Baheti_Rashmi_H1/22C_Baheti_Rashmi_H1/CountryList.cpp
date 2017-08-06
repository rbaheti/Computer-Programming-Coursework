// Implementation file for the CountryList class
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "CountryList.h"
#include "Country.h"
#include "ListNode.h"
using namespace std;

string formattedPopulation(int population) {
  string stringPopulation;
  while (population != 0) {
    int modulo = (population % 1000);
    population = population / 1000;

    char modulo_str[4] = "000";
    if (population != 0) {
      // Pad modulo with zeroes in the beginning if it does not have 3 digits in it.
      int temp_modulo = modulo / 10;
      int num_digits = 1;
      while (temp_modulo) {
        num_digits++;
        temp_modulo /= 10;
      }
      _itoa(modulo, modulo_str + 3 - num_digits, 10);
    }
    else {
      _itoa(modulo, modulo_str, 10);
    }

    if (stringPopulation.empty()) {
      stringPopulation = modulo_str;
    }
    else {
      stringPopulation = modulo_str + string(",") + stringPopulation;
    }
  }
  return stringPopulation;
}

//***************************************************************
// Constructor
//  - Allocates a sentinel node
//        --> an empty data node to be the first node in the list
//  - Set the counter to 0
//***************************************************************
CountryList::CountryList()
{
  head = new ListNode;
  head->SetNextListNode(NULL);
  cnt = 0;
}

//**************************************************
// displayList shows the country information
// stored in each node of the linked list
// pointed to by head.
//**************************************************

void CountryList::displayList() const
{
  ListNode *nodePtr;

  nodePtr = head->GetNextListNode();

  //Display the header
  cout << setfill('-');
  cout << left << setw(6) << "Code";
  cout << left << setw(20) << "Country";
  cout << left << setw(20) << "Capital";
  cout << right << setw(15) << "Population" << endl;
  for (int i = 0; i < 61; i++) { cout << '-'; }

  cout << endl << setfill(' ');
  while (nodePtr) {
    // Display the information in the current node.
    cout << left << setw(5) << nodePtr->GetCountry().GetCode() << " ";
    cout << left << setw(20) << nodePtr->GetCountry().GetName();
    cout << left << setw(20) << nodePtr->GetCountry().GetCapital();
    cout << right << setw(15) << formattedPopulation(nodePtr->GetCountry().GetPopulation()) << endl;

    // Move to the next node.
    nodePtr = nodePtr->GetNextListNode();
  }
  cout << endl;
}

//**************************************************
// The insertNode function inserts a node with
// countryIn copied to its country member.
//**************************************************
void CountryList::insertNode(Country countryIn)
{
  ListNode *newNode;             // A new node
  ListNode *nodePtr;             // To traverse the list
  ListNode *previousNode = NULL; // The previous node

                                 // Allocate a new node and store the country there.
  newNode = new ListNode;
  newNode->SetCountry(countryIn);

  previousNode = head;
  nodePtr = head->GetNextListNode();
  // Find the location of the new node in the sorted list
  while (nodePtr != NULL && strcmp(nodePtr->GetCountry().GetCode(), countryIn.GetCode()) < 0) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }
  // Update links and counter
  previousNode->SetNextListNode(newNode);
  newNode->SetNextListNode(nodePtr);
  cnt++;
}

//**************************************************
// The deleteNode function searches for a node
// with code as its code. The node, if found, is
// deleted from the list and from memory.
// It returns an error code
//      -1 represents an empty list
//      0 means the country was not found
//      1 means the country was deleted
//**************************************************
int CountryList::deleteNode(const char* code)
{
  ListNode *nodePtr;       // To traverse the list
  ListNode *previousNode = head;  // To point to the previous node

                                  // check if list is empty
  if (cnt == 0)
    return -1; // -1 for empty list

  nodePtr = head->GetNextListNode();
  // Search for the node to be deleted from the list
  while (nodePtr != NULL && strcmp(nodePtr->GetCountry().GetCode(), code) != 0) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }
  if (nodePtr) { // found
    previousNode->SetNextListNode(nodePtr->GetNextListNode());
    delete nodePtr;
    cnt--;
    return 1; // 1 for success
  }
  return 0; // 0 for not found
}

//**************************************************
// Searches the list for a given country code
//  - returns a pointer to the country if found
//  - returns NULL if the country cannot be found
//**************************************************
Country* CountryList::findCountry(const char* code) {
  ListNode *nodePtr;       // To traverse the list
  ListNode *previousNode;  // To point to the previous node

                           // If the list is empty, return NULL
  if (cnt == 0)
    return NULL;

  nodePtr = head->GetNextListNode();
  previousNode = head;

  while (nodePtr != NULL && strcmp(nodePtr->GetCountry().GetCode(), code)) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }

  if (nodePtr) { // found
    return nodePtr->GetCountryPtr();
  }
  return NULL;
}
//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************

CountryList::~CountryList()
{
  ListNode *nodePtr;   // To traverse the list
  ListNode *nextNode;  // To point to the next node

                       // Position nodePtr at the head of the list.
  nodePtr = head;

  // While nodePtr is not at the end of the list...
  while (nodePtr != NULL) {
    // Save a pointer to the next node.
    nextNode = nodePtr->GetNextListNode();
    // Delete the current node.
    delete nodePtr;
    // Position nodePtr at the next node.
    nodePtr = nextNode;
  }
}

Country* CountryList::findCountryWithLargestPopulation() {
  // If the list is empty, return NULL
  if (cnt == 0) {
    return NULL;
  }

  // To traverse the list
  ListNode *nodePtr = head->GetNextListNode();

  int largestPopulation = 0;
  Country* largestPopulationCountry = NULL;
  while (nodePtr != NULL) {
    if (nodePtr->GetCountry().GetPopulation() > largestPopulation) {
      largestPopulation = nodePtr->GetCountry().GetPopulation();
      largestPopulationCountry = nodePtr->GetCountryPtr();
    }
    nodePtr = nodePtr->GetNextListNode();
  }
  return largestPopulationCountry;
}
