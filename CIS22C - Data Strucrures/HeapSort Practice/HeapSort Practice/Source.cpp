#include <iostream>
#include <vector>
using namespace std;

void HeapRebuild(vector<int> & int_vec, int& parent, int& size) {
  int leftChild = 2 * parent + 1;
  int rightChild = 2 * parent + 2;

  if (leftChild >= size) {
    return;
  }
  else if (rightChild >= size) {
    if (int_vec[leftChild] > int_vec[parent]) {
      int temp = int_vec[parent];
      int_vec[parent] = int_vec[leftChild];
      int_vec[leftChild] = temp;
      HeapRebuild(int_vec, leftChild, size);
      return;
    }
    else {
      return;
    }
  }
  else {
    if (int_vec[parent] >= int_vec[leftChild] && int_vec[parent] >= int_vec[rightChild]) {
      return;
    }

    int biggerChild = (int_vec[leftChild] >= int_vec[rightChild]) ? leftChild : rightChild;

    int temp = int_vec[parent];
    int_vec[parent] = int_vec[biggerChild];
    int_vec[biggerChild] = temp;
    HeapRebuild(int_vec, biggerChild, size);
    return;
  }
}

int main() {

}