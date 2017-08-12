#include "IntBinaryTree.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  IntBinaryTree tree;
  tree.InsertNode(50);
  tree.InsertNode(60);
  tree.InsertNode(10);
  tree.InsertNode(55);
  tree.InsertNode(45);
  tree.InsertNode(70);
  tree.InsertNode(30);
  tree.InsertNode(16);
  tree.InsertNode(50);
  tree.DisplaySum();

  bool search = tree.SearchNode(5);
  if (search) {
    cout << "Your number '5' is in the list." << endl;
  }
  else 
    cout << "Your number '5' is not in the list." << endl;

  cin.get();
  return 0;
}