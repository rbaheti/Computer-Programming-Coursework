#ifndef _HEAP_H_
#define _HEAP_H_
#include <vector>
using namespace std;

class Heap {
public:
  Heap(int capacity);
 // ~Heap();
  bool IsEmpty() const;
  void Insert(int newItem);
  bool Delete(int &rootItem, int &comparison_count, int &swap_count);
  void RebuildHeap(int root, int &comparison_count, int &swap_count);
  void Print() const;

private:
  vector<int> items;
  // varialble size stores number of items in the heap
  int size;
  // variable capacity stores the maximum size of the heap
  const int capacity;
};

#endif
