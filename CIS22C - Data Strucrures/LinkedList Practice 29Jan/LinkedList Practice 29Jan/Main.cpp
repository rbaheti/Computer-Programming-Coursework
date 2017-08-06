#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;

int main() {
  LinkedList list;
  list.appendNode(10);
  list.appendNode(5);
  list.displayList();

  cin.get();
  return 0;
}