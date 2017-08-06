#ifndef INTSTACK_H
#define 

class Intstack {
private:
  struct StackNode {
    int value;
    StackNode *next;
  };
  StackNode *top;
  int count;

public:
  Intstack();
  ~Intstack();
  int getCount() { return count; }
  void push(int);
  void pop(int &);
  int getTop();
  bool isEmpty();
};


#endif
