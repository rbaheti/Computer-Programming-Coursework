// Specification file for the ListNode class
#ifndef LISTNODE_H
#define LISTNODE_H
#include "Country.h"

template <class T>
class ListNode
{
public:
  ListNode() {
    next = NULL;
    prev = NULL;
  }
  ~ListNode() {
  }
  void SetValue(T value) {
    this->value = value;
  }
  void SetNextListNode(ListNode *next) {
    this->next = next;
  }
  void SetPrevListNode(ListNode *prev) {
    this->prev = prev;
  }
  T GetValue() {
    return value;
  }
  T* GetValuePtr() {
    return &value;
  }
  ListNode* GetNextListNode() {
    return next;
  }
  ListNode* GetPrevListNode() {
    return prev;
  }

private:
  T value;
  ListNode *next;
  ListNode *prev;
};
#endif
