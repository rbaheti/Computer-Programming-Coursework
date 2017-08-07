#include"ListNode.h"

ListNode::ListNode() {
  next = NULL;
}
ListNode::~ListNode() {
}

void ListNode::SetCountry(Country country) {
  this->country = country;
}
void ListNode::SetNextListNode(ListNode *next) {
  this->next = next;
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