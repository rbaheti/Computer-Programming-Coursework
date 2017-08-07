#include "Heap.h"
#include <iostream>
using namespace std;

// Initializer list. 
Heap::Heap(int capacity_param) : items(capacity_param), capacity(capacity_param), size(0) {
}

bool Heap::IsEmpty() const {
  return (size == 0);
}

void Heap::Insert(int newItem) {
  if (size >= capacity) {
    cout << "Heap is full. You cannot add any more items now." << endl;
    return;
  }

  // Place the new item at the end of the heap
  items[size] = newItem;

  // Trickle new item up to its proper position
  int place = size;
  int parent = (place - 1) / 2;
  while ((parent >= 0) && (items[place] < items[parent])) {
    // Swap items[place] and items[parent]
    int temp = items[parent];
    items[parent] = items[place];
    items[place] = temp;

    place = parent;
    parent = (place - 1) / 2;
  }
  ++size;
}

bool Heap::Delete(int &rootItem, int &comparison_count, int &swap_count) {
  if (IsEmpty()) {
    cout << "Heap is empty." << endl;
    return false;
  }

  rootItem = items[0];
  items[0] = items[size - 1];
  --size;
  RebuildHeap(0, comparison_count, swap_count);
  return true;
}

void Heap::RebuildHeap(int root, int &comparison_count, int &swap_count) {
  int child = (2 * root) + 1;
  if (child < size) {
    ++comparison_count;
    int rightChild = child + 1;

    if ((rightChild < size) && items[rightChild] < items[child]) {
      child = rightChild;
    }

    if (items[root] > items[child]) {
      int temp = items[root];
      items[root] = items[child];
      items[child] = temp;
      ++swap_count;
      RebuildHeap(child, comparison_count, swap_count);
    }
  }
}

void Heap::Print() const {
  for (int i = 0; i < size; ++i) {
    cout << items[i] << endl;
  }
}