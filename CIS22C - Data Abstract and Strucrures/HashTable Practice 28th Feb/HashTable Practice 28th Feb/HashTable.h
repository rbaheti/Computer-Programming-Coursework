#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>
using namespace std;

class HashTable {
public:
  HashTable(int capacity);
  ~HashTable();
  void Insert(int* valuePtr);
  bool Find(int value);
  bool Erase(int value);

private:
  int capacity;

  vector<int**> buckets;
  vector<int*> overflow_bucket;
};
#endif
