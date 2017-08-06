#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
  head = new ListNode;
  head->next = NULL;
  count = 0;
}

LinkedList::~LinkedList() {
  ListNode *nodePtr = new ListNode;
  ListNode *preNode = NULL;
  nodePtr = head->next;
  while (nodePtr != NULL) {
    preNode = nodePtr;
    nodePtr = nodePtr->next;
    delete preNode;
  }
}

void LinkedList::displayList() {
  while (!head->next) {
    cout << "The list is empty" << endl;
    return;
  }
  ListNode *nodePtr = head->next;
  while (nodePtr != NULL) {
    cout << nodePtr->value << endl;
    nodePtr = nodePtr->next;
  }
}

void LinkedList::appendNode(int num) {
  ListNode *newNode = new ListNode;
  newNode->value = num;
  newNode->next = NULL;

  while (!head->next) {
    head->next = newNode;
    return;
  }
  ListNode *nodePtr = head->next;
  cout << "Value b4 while:" << nodePtr->value << endl;
  ListNode *prevNode = NULL;
  while (nodePtr != NULL && nodePtr->value > num) {
    cout << "Value in while loop:" << nodePtr->value << endl;
    prevNode = nodePtr;
    nodePtr = nodePtr->next;
  }
  cout << "Value after while loop:" << prevNode->value << endl;
  prevNode = newNode;
  newNode->next = nodePtr;
}

