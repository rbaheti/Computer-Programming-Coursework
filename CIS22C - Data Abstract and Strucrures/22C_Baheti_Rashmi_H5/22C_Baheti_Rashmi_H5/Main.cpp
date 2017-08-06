#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <vector>
using namespace std;

void HeapRebuild(vector<int>& int_vec, int parent, const int size, 
  int &comparison_count, int &swap_count) {
  int leftChild = 2 * parent + 1;
  int rightChild = 2 * parent + 2;

  if (leftChild >= size) {
    return;
  }
  else if (rightChild >= size) {
    ++comparison_count;
    if (int_vec[parent] < int_vec[leftChild]) {
      ++swap_count;
      int temp = int_vec[parent];
      int_vec[parent] = int_vec[leftChild];
      int_vec[leftChild] = temp;
      HeapRebuild(int_vec, leftChild, size, comparison_count, swap_count);
      return;
    }
    else {
      return;
    }
  }
  else {
    comparison_count += 2;
    if (int_vec[parent] >= int_vec[leftChild] && int_vec[parent] >= int_vec[rightChild]) {
      return;
    }

    ++comparison_count;
    int biggerChild = (int_vec[leftChild] >= int_vec[rightChild]) ? leftChild : rightChild;

    ++swap_count;
    int temp = int_vec[parent];
    int_vec[parent] = int_vec[biggerChild];
    int_vec[biggerChild] = temp;
    HeapRebuild(int_vec, biggerChild, size, comparison_count, swap_count);
    return;
  }
}

void HeapSort(vector<int>& int_vec, int &comparison_count, int &swap_count) {
  for (int parent = int_vec.size() - 1; parent >= 0; --parent) {
    HeapRebuild(int_vec, parent, int_vec.size(), comparison_count, swap_count);
  }

  int remaining_heap_size = int_vec.size();
  for (int i = 0; i < int_vec.size() - 1; ++i) {
    ++swap_count;
    int temp = int_vec[0];
    int_vec[0] = int_vec[remaining_heap_size - 1];
    int_vec[remaining_heap_size - 1] = temp;
    
    --remaining_heap_size;
    HeapRebuild(int_vec, 0, remaining_heap_size, comparison_count, swap_count);
  }
}

void SelectionSort(vector<int>& int_vec, int &comparison_count, int &swap_count) {
  int minIndex = 0;
  for (int i = 0; i < int_vec.size() - 1; ++i) {
    minIndex = i;
    for (int j = i + 1; j < int_vec.size(); ++j) {
      ++comparison_count;
      if (int_vec[minIndex] > int_vec[j]) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      ++swap_count;
      int temp = int_vec[minIndex];
      int_vec[minIndex] = int_vec[i];
      int_vec[i] = temp;
    }
  }
}

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

  if (capacity <= 100) {
    cout << "Unsorted values are: " << endl;
  }
  // generate random number between -99 and 99:
  for (int i = 0; i < capacity; ++i) {
    randomValue = rand() % 198;
    randomValue -= 99;
    heapSort_vec.push_back(randomValue);
    selectionSort_vec.push_back(randomValue);
    if (capacity <= 100) {
      cout << randomValue << " ";
    }
  }
  cout << endl << endl;

  int comparison_count = 0, swap_count = 0;
  HeapSort(heapSort_vec, comparison_count, swap_count);
  if (capacity <= 100) {
    cout << "Sorted values using Heap Sort are: " << endl;
    for (int i = 0; i < heapSort_vec.size(); ++i) {
      cout << heapSort_vec[i] << " ";
    } 
    cout << endl << endl;
  }
  cout << "Heap Sort Statistics: " << endl;
  cout << "The number of data comparisons is: " << comparison_count << endl;
  cout << "The number of data moves is: " << swap_count << endl << endl;
  
  comparison_count = 0, swap_count = 0;
  SelectionSort(selectionSort_vec, comparison_count, swap_count);
  if (capacity <= 100) {
    cout << "Sorted values using Selection Sort are: " << endl;
    for (int i = 0; i < selectionSort_vec.size(); ++i) {
      cout << selectionSort_vec[i] << " ";
    }
    cout << endl << endl;
  }  
  cout << "Selection Sort Statistics: " << endl;
  cout << "The number of data comparisons is: " << comparison_count << endl;
  cout << "The number of data moves is: " << swap_count << endl << endl;
  
  cin.get();
  cin.get();
  return 0;
}

/********************************************************************
                            SAMPLE OUTPUT
*********************************************************************
Please enter the number of items you want to sort: 10
Unsorted values are:
-81 -28 -75 -46 -12 43 -10 -93 -55 -54

Sorted values using Heap Sort are:
-93 -81 -75 -55 -54 -46 -28 -12 -10 43

Heap Sort Statistics:
The number of data comparisons is: 50
The number of data moves is: 24

Sorted values using Selection Sort are:
-93 -81 -75 -55 -54 -46 -28 -12 -10 43

Selection Sort Statistics:
The number of data comparisons is: 45
The number of data moves is: 8

---------------******************************************-------------------
Please enter the number of items you want to sort: 100
Unsorted values are:
-38 -52 32 42 8 13 -33 -96 -73 -73 78 -44 98 -43 -47 96 -91 -50 -63 -20 -26 -12 -99 -87 51 1 -80 -97
59 56 61 90 9 -28 85 -70 14 56 -58 69 46 57 82 -74 -94 4 62 -41 84 -80 -58 49 -88 -97 -23 21 85 46
-94 64 79 90 -87 29 -37 -6 -12 44 -85 -12 -44 14 -58 26 85 66 95 -91 75 1 -47 28 10 -7 42 87 81 -67
-35 -86 72 32 -82 77 -83 80 47 -79 93 95

Sorted values using Heap Sort are:
-99 -97 -97 -96 -94 -94 -91 -91 -88 -87 -87 -86 -85 -83 -82 -80 -80 -79 -74 -73 -73 -70 -67 -63 -58
-58 -58 -52 -50 -47 -47 -44 -44 -43 -41 -38 -37 -35 -33 -28 -26 -23 -20 -12 -12 -12 -7 -6 1 1 4 8 9
10 13 14 14 21 26 28 29 32 32 42 42 44 46 46 47 49 51 56 56 57 59 61 62 64 66 69 72 75 77 78 79 80 8
1 82 84 85 85 85 87 90 90 93 95 95 96 98

Heap Sort Statistics:
The number of data comparisons is: 1507
The number of data moves is: 582

Sorted values using Selection Sort are:
-99 -97 -97 -96 -94 -94 -91 -91 -88 -87 -87 -86 -85 -83 -82 -80 -80 -79 -74 -73 -73 -70 -67 -63 -58
-58 -58 -52 -50 -47 -47 -44 -44 -43 -41 -38 -37 -35 -33 -28 -26 -23 -20 -12 -12 -12 -7 -6 1 1 4 8 9
10 13 14 14 21 26 28 29 32 32 42 42 44 46 46 47 49 51 56 56 57 59 61 62 64 66 69 72 75 77 78 79 80 8
1 82 84 85 85 85 87 90 90 93 95 95 96 98

Selection Sort Statistics:
The number of data comparisons is: 4950
The number of data moves is: 90

---------------******************************************-------------------

Please enter the number of items you want to sort: 1000

Heap Sort Statistics:
The number of data comparisons is: 24894
The number of data moves is: 9062

Selection Sort Statistics:
The number of data comparisons is: 499500
The number of data moves is: 987

---------------******************************************-------------------
Please enter the number of items you want to sort: 10000

Heap Sort Statistics:
The number of data comparisons is: 348709
The number of data moves is: 123778

Selection Sort Statistics:
The number of data comparisons is: 49995000
The number of data moves is: 9953

***********************************************************************************/