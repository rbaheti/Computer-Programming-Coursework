#include <iostream>
using namespace std;
#include"NumberList.h"

int main() {
  NumberList list;
  list.appendNode(10);
  list.appendNode(20);
  list.appendNode(30);
  list.insertNode(5);
  list.displayList();
  list.reverseDisplayList();
  list.deleteNode(5);
  list.displayList();
  list.reverseDisplayList();

  cin.get();
  return 0;
}