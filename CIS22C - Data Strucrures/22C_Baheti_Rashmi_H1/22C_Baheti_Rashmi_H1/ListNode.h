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
  Country GetCountry();
  Country* GetCountryPtr();
  ListNode* GetNextListNode();

private:
  Country country;
  ListNode *next;
};

#endif
