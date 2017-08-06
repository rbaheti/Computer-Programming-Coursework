#include <iostream>
using namespace std;
#include "NumberList.h"

NumberList::NumberList() {
  head = NULL;
  last = NULL;
}
NumberList::~NumberList() {
  Node *nodePtr = head;
  Node *prevNode = NULL;
  while (nodePtr != NULL) {
    prevNode = nodePtr;
    nodePtr = nodePtr->next;
    delete prevNode;
  }
}

void NumberList::displayList() {
  if (!head) {
    cout << "The list is empty!" << endl;
    return;
  }
  Node *nodePtr = head;
  while (nodePtr != NULL) {
    cout << "Current nodePtr value is: ";
    cout << nodePtr->value << endl;
    nodePtr = nodePtr->next;
  }
  cout << "Exiting while loop!" << endl;
}

void NumberList::reverseDisplayList() {
  if (!last) {
    cout << "The reverse list is empty!" << endl;
    return;
  }

  Node *nodePtr = last;
  while (nodePtr != NULL) {
    cout << "Current nodePtr value is: ";
    cout << nodePtr->value << endl;
    nodePtr = nodePtr->prev;
  }
  cout << "Exiting reverse while loop!" << endl;
}

void NumberList::appendNode(int num) {
  Node *newNode = new Node;
  newNode->value = num;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (!head) {
    head = newNode;
    last = newNode;
    return;
  }

  last->next = newNode;
  newNode->prev = last;
  last = newNode;
}

void NumberList::insertNode(int num) {
  Node *newNode = new Node;
  newNode->next = NULL;
  newNode->prev = NULL;
  newNode->value = num;

  if (!head) {
    head = newNode;
    last = newNode;
    return;
  }

  Node *nodePtr = head;
  Node *prevNode = NULL;
  while (nodePtr != NULL && nodePtr->value < num) {
    prevNode = nodePtr;
    nodePtr = nodePtr->next;
  }

  if (prevNode == NULL) {
    // Element is being added before head.
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
    return;
  }
  prevNode->next = newNode;
  newNode->prev = prevNode;

  if (nodePtr == NULL) {
    // Element is being added after last.
    last = newNode;
    return;
  }

  // Element is being added somewhere in the middle (i.e. before nodePtr).
  newNode->next = nodePtr;
  nodePtr->prev = newNode;
}

void NumberList::deleteNode(int num) {
  if (!head) {
    cout << "The list is empty. Number cannot be deleted." << endl;
    return;
  }

  Node *nodePtr = head;
  Node *prevNode = NULL;
  while (nodePtr != NULL && nodePtr->value < num) {
    prevNode = nodePtr;
    nodePtr = nodePtr->next;
  }
  if (nodePtr == NULL || nodePtr->value != num) {
    return;
  }

  if (nodePtr == head) {
    Node *temp = nodePtr->next;
    if (temp) {
      // This can happen when there is only one element in the linked list.
      temp->prev = NULL;
    }
    delete nodePtr;
    head = temp;
    return;
  }

  if (nodePtr == last) {
    last = prevNode;
    if (last) {
      // This can happen when there is only one element in the linked list.
      last->next = NULL;
    }
    delete nodePtr;
    return;
  }
  
  prevNode->next = nodePtr->next;
  nodePtr->next->prev = prevNode;
  delete nodePtr;
}

/*int NumberList::midValue() {
  if (!head) {
    return -1;
  }
  Node *nodePtr = head;
  Node *midnum = head;
  Node *prevNode = NULL;
  while (midnum != NULL) {
    prevNode = nodePtr;
    nodePtr = nodePtr->next;
    if (midnum->next == NULL) {
      break;
    }
    midnum = midnum->next->next;
  }
  return prevNode->value;
}*/