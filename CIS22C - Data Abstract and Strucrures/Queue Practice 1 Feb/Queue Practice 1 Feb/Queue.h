#ifndef QUEUE_H
#define QUEUE_H
#include <string>

class Queue {
private:
  struct QueueNode {
    int value;
    QueueNode* next;
  };
  QueueNode* front;
  QueueNode* rear;
  int count;

public:
  Queue() { front = rear = NULL; count = NULL;}
  ~Queue();
  int getCount() {return count;}
  bool isEmpty() {return count == 0;}
  bool getFront(int &);
  bool getRear(int &);
  bool enqueue();
  bool dequeue(int &);
};
#endif
