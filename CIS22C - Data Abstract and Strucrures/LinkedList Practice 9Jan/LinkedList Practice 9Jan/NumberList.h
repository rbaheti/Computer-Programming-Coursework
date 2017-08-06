#ifndef _NUMBERLIST_
#define _NUMBERLIST_

class NumberList {
private:
  struct Node {
    int value;
    Node *next;
    Node *prev;
  };

  Node *head;
  Node *last;

public:
  NumberList();
  ~NumberList();
  void displayList();
  void reverseDisplayList();
  void appendNode(int);
  void insertNode(int);
  void deleteNode(int);
  /*int midValue();*/
};
#endif
