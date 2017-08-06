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
  
  /*list.insertNode(40);
  list.insertNode(15);
  list.insertNode(60);
  list.displayList();
  cout << endl;
  //
  //list.displayList();
  int value = list.midValue();
  cout << "Midvalue = " << value << endl;*/

  cin.get();
  return 0;
}