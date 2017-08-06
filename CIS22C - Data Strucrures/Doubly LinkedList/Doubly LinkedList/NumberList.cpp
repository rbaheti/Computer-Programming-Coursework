#include <iostream>
using namespace std;
#include "NumberList.h"

NumberList::NumberList() {
  head = NULL;
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
void NumberList::appendNode(int num) {
  Node *newNode = new Node;
  newNode->value = num;
  newNode->next = NULL;

  if (!head) {
    head = newNode;
    return;
  }

  Node *nodePtr = head;
  while (nodePtr->next != NULL) {
    nodePtr = nodePtr->next;
  }
  nodePtr->next = newNode;
  return;
}

void NumberList::insertNode(int num) {
  Node *newNode = new Node;
  newNode->next = NULL;
  newNode->value = num;

  if (!head) {
    head = newNode;
    return;
  }

  Node *nodePtr = head;
  Node *prevNode = NULL;
  while (nodePtr != NULL && nodePtr->value < num) {
    prevNode = nodePtr;
    nodePtr = nodePtr->next;
  }

  if (prevNode == NULL) {
    newNode->next = head;
    head = newNode;
    return;
  }
  prevNode->next = newNode;
  newNode->next = nodePtr;
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
  if (nodePtr == NULL) {
    return;
  }
  if (nodePtr->value == num) {
    prevNode->next = nodePtr->next;
    delete nodePtr;
    return;
  }
}

void NumberList::displayList() {
  Node *nodePtr = head;
  if (!head) {
    cout << "The list is empty!" << endl;
    return;
  }
  while (nodePtr != NULL) {
    cout << "Current nodePtr value is: ";
    cout << nodePtr->value << endl;
    nodePtr = nodePtr->next;
  }
  cout << "Exiting while loop!" << endl;
  return;
}

void NumberList::reverseList() {
  Node *nodePtr = NULL;
}

int NumberList::midValue() {
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
}