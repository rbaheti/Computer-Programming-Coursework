#ifndef _NUMBERLIST_
#define _NUMBERLIST_

class NumberList {
private:
  struct Node {
    int value;
    Node *next;
  };

  Node *head;

public:
  NumberList();
  ~NumberList();
  void appendNode(int);
  void insertNode(int);
  void deleteNode(int);
  void displayList();
  void reverseList();
  int midValue();
};
#endif
