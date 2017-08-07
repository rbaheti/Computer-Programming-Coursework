// Specification file for the LinkedList class
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "ListNode.h"
using namespace std;

string formattedPopulation(int population);

template <class T>
class LinkedList
{
private:
  ListNode<T> *head;  // pointer to the first node in the list
  int count;         // keeps track of the number of countries in the list

public:
  LinkedList();
  ~LinkedList();
  // Basic Linked List Operations
  int getCount() { return count; }
  ListNode<T>* GetHead();
  void insertNode(T insert_value);
  int deleteNode(T delete_value);
  void displayListForward() const;
  void displayListBackward() const;
  T* findValue(T find_value);
};

template <class T>
ListNode<T>* LinkedList<T>::GetHead() {
  return head;
}

//***************************************************************
// Constructor
//  - Allocates a sentinel node
//        --> an empty data node to be the first node in the list
//  - Set the counter to 0
//***************************************************************
template <class T>
LinkedList<T>::LinkedList() {
  head = new ListNode<T>;
  head->SetNextListNode(head);
  head->SetPrevListNode(head);
  count = 0;
}

//**************************************************
// Destructor
// This function deletes every node in the list.
//**************************************************
template <class T>
LinkedList<T>::~LinkedList() {
  {
    ListNode<T> *nodePtr;   // To traverse the list
    ListNode<T> *nextNode;  // To point to the next node

                                  // Position nodePtr at the head of the list.
    nodePtr = head;

    // While nodePtr is not at the end of the list...
    while (nodePtr != head) {
      // Save a pointer to the next node.
      nextNode = nodePtr->GetNextListNode();
      // Delete the current node.
      delete nodePtr;
      // Position nodePtr at the next node.
      nodePtr = nextNode;
    }
  }
}



//**************************************************
// The insertNode function inserts a node with
// value copied to its T member.
//**************************************************
template <class T>
void LinkedList<T>::insertNode(T insert_value) {
  ListNode<T> *newNode;             // A new node
  ListNode<T> *nodePtr;             // To traverse the list
  ListNode<T> *previousNode = NULL; // The previous node

                                    // Allocate a new node and store the T there.
  newNode = new ListNode<T>;        // Constructor sets the next and prev to NULL. 
                                    // Hence, no need to do here explicitly.
  newNode->SetValue(insert_value);

  previousNode = head;
  nodePtr = head->GetNextListNode();
  // Find the location of the new node in the sorted list
  while (nodePtr != head && nodePtr->GetValue() < insert_value) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }
  // Update links and counter
  previousNode->SetNextListNode(newNode);
  newNode->SetPrevListNode(previousNode);
  newNode->SetNextListNode(nodePtr);
  nodePtr->SetPrevListNode(newNode);
  count++;
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
template <class T>
int LinkedList<T>::deleteNode(T delete_value) {
  if (count == 0)// check if list is empty
    return -1; // -1 for empty list

  ListNode<T> *nodePtr;       // To traverse the list
  ListNode<T> *previousNode = head;  // To point to the previous node
  nodePtr = head->GetNextListNode();
  // Search for the node to be deleted from the list
  while (nodePtr != head && nodePtr->GetValue() < delete_value) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }

  if (nodePtr->GetValue() == delete_value) { // found
    previousNode->SetNextListNode(nodePtr->GetNextListNode());
    nodePtr->GetNextListNode()->SetPrevListNode(previousNode);
    delete nodePtr;
    count--;
    return 1; // 1 for success
  }
  return 0; // 0 for not found
}

//**************************************************
// displayListForward shows the country information
// stored in each node of the linked list
// pointed to by head.
//**************************************************
template <class T>
void LinkedList<T>::displayListForward() const {
  for (int i = 0; i < 61; i++) { cout << '-'; }

  cout << endl << setfill(' ');
  ListNode<T> *nodePtr;
  nodePtr = head->GetNextListNode();
  while (nodePtr != head) {
    // Display the information in the current node.
    cout << nodePtr->GetValue() << endl;

    // Move to the next node.
    nodePtr = nodePtr->GetNextListNode();
  }
  cout << endl;
}

//**************************************************
// displayListBackward shows the country information
// stored in each node of the linked list
// pointed to by last.
//**************************************************
template <class T>
void LinkedList<T>::displayListBackward() const {
  for (int i = 0; i < 61; i++) { cout << '-'; }
  cout << endl << setfill(' ');

  ListNode<T> *nodePtr = head->GetNextListNode();
  ListNode<T> *previousNode = head; // The previous node
  while (nodePtr != head) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }
  nodePtr = previousNode;
  if (nodePtr == head) {
    cout << "The list is empty!";
  }
  while (nodePtr != head) {
    // Display the information in the current node.
    cout << nodePtr->GetValue() << endl;

    // Move to the next node.
    nodePtr = nodePtr->GetPrevListNode();
  }
  cout << endl;
}

//**************************************************
// Searches the list for a given country code
//  - returns a pointer to the country if found
//  - returns NULL if the country cannot be found
//**************************************************
template <class T>
T* LinkedList<T>::findValue(T find_value) {
  ListNode<T> *nodePtr;       // To traverse the list
  ListNode<T> *previousNode;  // To point to the previous node

                                    // If the list is empty, return NULL
  if (count == 0)
    return NULL;

  nodePtr = head->GetNextListNode();
  previousNode = head;

  // We compare the values using the overloaded comparison operators in them.
  while (nodePtr != head && nodePtr->GetValue() < find_value) {
    previousNode = nodePtr;
    nodePtr = nodePtr->GetNextListNode();
  }
  if (nodePtr->GetValue() == find_value) {
    return nodePtr->GetValuePtr();
  }
  return NULL;
}
#endif

