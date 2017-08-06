#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string>
#include <vector>
#include "hash-table.h"

using namespace std; 

int main() {
  HashTable ht(10);

  // Dynamically allocate integer and insert it in hash table.
  ht.Insert(new int(10));
  cout << "Is 10 found: " << ht.Search(10) << endl;
  cout << "Is 20 found: " << ht.Search(20) << endl;

  // Insert 5 more numbers. First 3 belong to same bucket as 10 and hence will cause overflow.
  ht.Insert(new int(20));
  ht.Insert(new int(30));
  ht.Insert(new int(40));
  ht.Insert(new int(63));
  ht.Insert(new int(72));

  cout << "Is 20 found: " << ht.Search(20) << endl;
  cout << "Is 30 found: " << ht.Search(30) << endl;
  cout << "Is 40 found: " << ht.Search(40) << endl;
  cout << "Is 63 found: " << ht.Search(63) << endl;
  cout << "Is 72 found: " << ht.Search(72) << endl;
  cout << "Is 99 found: " << ht.Search(99) << endl;

  getchar();
  return 0;
}