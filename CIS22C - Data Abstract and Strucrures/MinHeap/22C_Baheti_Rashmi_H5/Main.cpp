#include "Heap.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
using namespace std;

void HeapSort(vector<int>* int_vec, int &comparison_count, int &swap_count);
void SelectionSort(vector<int>* int_vec, int &comparison_count, int &swap_count);

int main() {
  int capacity = 0;
  cout << "Please enter the number of items you want to sort: ";
  cin >> capacity;

  // Input validation
  if (capacity <= 0) {
    cout << "There are no values to sort." << endl;
    cin.get(); 
    cin.get();
    return 0;
  }

  // initialize random seed: 
  srand(time(NULL));
  int randomValue = 0;
  // Initializing vectors to store random numbers
  vector<int> heapSort_vec;
  vector<int> selectionSort_vec;
  cout << "Unsorted values are: " << endl;
  // generate random number between -99 and 99:
  for (int i = 0; i < capacity; ++i) {
    randomValue = rand() % 198;
    randomValue -= 99;
    heapSort_vec.push_back(randomValue);
    selectionSort_vec.push_back(randomValue);
    cout << randomValue << " ";
  }
  cout << endl << endl;

  int comparison_count = 0, swap_count = 0;
  HeapSort(&heapSort_vec, comparison_count, swap_count);
  cout << "Sorted values using Heap Sort are: " << endl;
  for (int i = 0; i < heapSort_vec.size(); ++i) {
    cout << heapSort_vec[i] << " ";
  }
  cout << endl;
  cout << "The number of data comparisons is: " << comparison_count << endl;
  cout << "and the number of data moves is: " << swap_count << endl << endl;

  comparison_count = 0, swap_count = 0;
  SelectionSort(&selectionSort_vec, comparison_count, swap_count);
  cout << "Sorted values using Selection Sort are: " << endl;
  for (int i = 0; i < selectionSort_vec.size(); ++i) {
    cout << selectionSort_vec[i] << " ";
  }
  cout << endl;
  cout << "The number of data comparisons is: " << comparison_count << endl;
  cout << "and the number of data moves is: " << swap_count << endl << endl;

  cin.get();
  cin.get();
  return 0;
}

void HeapSort(vector<int>* int_vec, int &comparison_count, int &swap_count) {
  Heap heap(int_vec->size());
  // Insert values in the heap
  for (int i = 0; i < int_vec->size(); ++i) {
    heap.Insert(int_vec->at(i));
  }
  // Sort values using heap
  int sortValue = 0;
  for (int i = 0; i < int_vec->size(); ++i) {
    heap.Delete(sortValue, comparison_count, swap_count);
    (*int_vec)[i] = sortValue;
  }
}

void SelectionSort(vector<int>* int_vec, int &comparison_count, int &swap_count) {
  int minIndex = 0, minValue = 0;
  for (int i = 0; i < int_vec->size()-1; ++i) {
    minIndex = i;
    minValue = (*int_vec)[i];
    for (int j = i+1; j < int_vec->size(); ++j) {
      ++comparison_count;
      if (minValue > (*int_vec)[j]) {
        minValue = (*int_vec)[j];
        minIndex = j;
        ++swap_count;
      }
    }
    (*int_vec)[minIndex] = (*int_vec)[i];
    (*int_vec)[i] = minValue;
  }
}