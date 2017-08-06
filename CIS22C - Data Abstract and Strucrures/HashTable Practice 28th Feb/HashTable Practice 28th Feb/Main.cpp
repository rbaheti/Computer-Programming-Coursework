#include "HashTable.h"
#include <iostream>
using namespace std;

int main() {
  HashTable h1(5);
  h1.Insert(new int(10));
  h1.Insert(new int(20));
  h1.Insert(new int(30));
  h1.Insert(new int(40));
  h1.Insert(new int(50));
  cout << "Value 10 found: " << h1.Find(10) << endl;
  cout << "Value 20 found: " << h1.Find(20) << endl;
  cout << "Value 30 found: " << h1.Find(30) << endl;
  cout << "Value 40 found: " << h1.Find(40) << endl;
  cout << "Value 50 found: " << h1.Find(50) << endl;
  h1.Erase(20);
  h1.Erase(50);
  cout << "Value 20 found: " << h1.Find(20) << endl;
  cout << "Value 50 found: " << h1.Find(50) << endl;
  cin.get();
  return 0;
}