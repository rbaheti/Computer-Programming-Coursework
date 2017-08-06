#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class LinkedList {
private:
  struct ListNode {
    int value;
    ListNode* next;
  };
  ListNode *head;
  int count;

public:
  LinkedList();
  ~LinkedList();
  int getCount() { return count; }
  void displayList();
  void appendNode(int num);
  void insertNode(int num);
  void deleteNode(int num);
};



#endif
