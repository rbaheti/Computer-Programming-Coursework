#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class HashTable {
public:
  HashTable(int capacity);
  ~HashTable();

  void Insert(int* valuePtr);
  bool Search(int value);

private:
  int capacity;
  int current_size;

  vector<int**> buckets;
  vector<int*> overflow_bucket;
};