#include"ListNode.h"

ListNode::ListNode() {
  next = NULL;
  prev = NULL;
}
ListNode::~ListNode() {
}

void ListNode::SetCountry(Country country) {
  this->country = country;
}

void ListNode::SetNextListNode(ListNode *next) {
  this->next = next;
}

void ListNode::SetPrevListNode(ListNode *prev) {
  this->prev = prev;
}

Country ListNode::GetCountry() {
  return country;
}

Country* ListNode::GetCountryPtr() {
  return &country;
}

ListNode* ListNode::GetNextListNode() {
  return next;
}

ListNode* ListNode::GetPrevListNode() {
  return prev;
}