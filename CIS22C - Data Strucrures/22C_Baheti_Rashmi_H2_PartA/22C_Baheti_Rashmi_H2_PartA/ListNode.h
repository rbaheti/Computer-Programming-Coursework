// Specification file for the ListNode class
#ifndef LISTNODE_H
#define LISTNODE_H
#include "Country.h"

class ListNode
{
public:
  ListNode();
  ~ListNode();
  void SetCountry(Country country);
  void SetNextListNode(ListNode *next);
  void SetPrevListNode(ListNode *prev);
  Country GetCountry();
  Country* GetCountryPtr();
  ListNode* GetNextListNode();
  ListNode* GetPrevListNode();

private:
  Country country;
  ListNode *next;
  ListNode *prev;
};

#endif
