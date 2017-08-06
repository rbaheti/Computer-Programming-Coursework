#include "HashTable.h"
#include <iostream>
using namespace std;

#define BUCKET_SIZE 3

HashTable::HashTable(int capacity) {
  this->capacity = capacity;
  for (int i = 0; i < capacity; ++i) {
    int** bucket = new int*[BUCKET_SIZE];
    buckets.push_back(bucket);

    for (int j = 0; j < BUCKET_SIZE; ++j) {
      buckets[i][j] = NULL;
    }
  }
}

HashTable::~HashTable() {
  for (int i = 0; i < capacity; ++i) {
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j]) {
        delete buckets[i][j];
      }
    }
    delete[] buckets[i];
  }
}

void HashTable::Insert(int *valuePtr) {
  int bucket_no = *valuePtr % capacity;
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (!buckets[bucket_no][j]) {
      buckets[bucket_no][j] = valuePtr;
      return;
    }
  }
  overflow_bucket.push_back(valuePtr);
}

bool HashTable::Find(int value) {
  int bucket_no = value % capacity;
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (buckets[bucket_no][j] && *buckets[bucket_no][j] == value) {
      return true;
    }
  }
  for (int i = 0; i < overflow_bucket.size(); ++i){
    if (*overflow_bucket[i] == value) {
      cout << "Value found: " << value << endl;
      return true;
    }
  }
  return false;
}

bool HashTable::Erase(int value) {
  int bucket_no = value % capacity;
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (buckets[bucket_no][j] && *buckets[bucket_no][j] == value) {
      delete buckets[bucket_no][j];
      return true;
    }
  }
  for (int i = 0; i < overflow_bucket.size(); ++i) {
    if (*overflow_bucket[i] == value) {
      cout << "Value found: " << value << endl;
      delete overflow_bucket[i];
      overflow_bucket.erase(overflow_bucket.begin() + i);
      return true;
    }
  }
  return false;
}