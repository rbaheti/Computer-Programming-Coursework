#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <vector>
#include <string>
#include <iomanip>
using namespace std;

#define BUCKET_SIZE 3

template <class T>
class HashTable {
public:
  // HashTable Constructor
  HashTable(int capacity);
  // HashTable Destructor
  ~HashTable();
  // Hash function hashes the key.
  int Hash(string key);
  // Insert function inserts a HashTableNode using key 
  // to find the location in the Hash Table
  void Insert(string key, T* insert_valuePtr);
  T* Find(string key);
  T* Erase(string key);
  void PrintHashTable(void visit(T *));
  void PrintStats();
  void InsertValuesIntoVector(vector<T*>* vec);

private:
  struct HashTableNode {
    // HashTableNode constructor
    HashTableNode() {
      value = NULL;
    }
    string key;
    T* value;
  };

  // num_buckets stores the number of buckets in the primary storage space
  int num_buckets;
  // current_size stores the number of elements in the Hash Table
  int current_size;
  // primary storage space
  vector<HashTableNode*> buckets;
  // secondary storage space
  vector<HashTableNode> overflow_bucket;
};

//**************************************************
// HashTable constructor initializes buckets with
// the number of bucket.
//**************************************************
template <class T>
HashTable<T>::HashTable(int num_buckets) {
  this->num_buckets = num_buckets;

  for (int i = 0; i < num_buckets; ++i) {
    HashTableNode* bucket = new HashTableNode[BUCKET_SIZE];
    buckets.push_back(bucket);
  }
}

//**************************************************
// Destructor deletes all the items in the bucket
// and then deletes the buckets[].
//**************************************************
template <class T>
HashTable<T>::~HashTable() {
  for (int i = 0; i < num_buckets; ++i) {
    // Delete all items in this bucket.
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j].value) {
        delete buckets[i][j].value;
        buckets[i][j].value = NULL;
      }
    }
    delete[] buckets[i];
  }
  for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
    delete overflow_bucket[i].value;
    overflow_bucket[i].value = NULL;
  }
}

//**************************************************
// Hash function hashes the key.
//**************************************************
template <class T>
int HashTable<T>::Hash(string key) {
  int sum = 0;
  for (unsigned int i = 0; i < key.size(); ++i) {
    sum += key.at(i);
  }

  return sum % num_buckets;
}

//**************************************************
// The Insert function inserts a node with
// value copied to its T member.
//**************************************************
template <class T>
void HashTable<T>::Insert(string key, T* insert_valuePtr) {
  ++current_size;
  int bucket_no = Hash(key);

  // Insert in primary bucket at 'bucket_no' index.
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (!buckets[bucket_no][j].value) {
      buckets[bucket_no][j].key = key;
      buckets[bucket_no][j].value = insert_valuePtr;
      return;
    }
  }
  // Insert in overflow bucket.
  HashTableNode hashTableNode;
  hashTableNode.key = key;
  hashTableNode.value = insert_valuePtr;
  overflow_bucket.push_back(hashTableNode);
}

//**************************************************
// The Find function finds a node with
// value copied to its T member.
//**************************************************
template <class T>
T* HashTable<T>::Find(string key) {
  int bucket_no = Hash(key);

  // Search in primary bucket at 'bucket_no' index.
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (buckets[bucket_no][j].value && buckets[bucket_no][j].key == key) {
      return buckets[bucket_no][j].value;
    }
  }

  // Search in overflow bucket.
  for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
    if (overflow_bucket[i].key == key)
      return overflow_bucket[i].value;
  }
  return NULL;
}

//**************************************************
// The Erase function erases a node with
// value copied to its T member.
//**************************************************
template <class T>
T* HashTable<T>::Erase(string key) {
  T* return_value = NULL;
  int bucket_no = Hash(key);

  // Search and erase in primary bucket at 'bucket_no' index.
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (buckets[bucket_no][j].value && buckets[bucket_no][j].key == key) {
      --current_size;
      buckets[bucket_no][j].key.clear();
      T* value_copy = buckets[bucket_no][j].value;
      buckets[bucket_no][j].value = NULL;
      return_value = value_copy;
      break;
    }
  }

  int total_elements = 0;
  // Iterate through each item in this bucket.
  for (int j = 0; j < BUCKET_SIZE; ++j) {
    if (buckets[bucket_no][j].value) {
      ++total_elements;
    }
  }
  // Search and move T* to bucket.
  if (total_elements == 0) {
    for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
      if (overflow_bucket[i].key == key) {
        buckets[bucket_no][0].value = overflow_bucket[i].value;
        buckets[bucket_no][0].key = overflow_bucket[i].key;
        overflow_bucket[i].key.clear();
        overflow_bucket.erase(overflow_bucket.begin() + i);
        break;
      }
    }
  }

  // If required key is found and erased from the bucket, then return
  if (return_value) {
    return return_value;
  }

  // If the required key is not found in the buckets, 
  // then search and erase it from overflow bucket.
  for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
    if (overflow_bucket[i].key == key) {
      --current_size;
      overflow_bucket[i].key.clear();
      T* value_copy = overflow_bucket[i].value;
      overflow_bucket.erase(overflow_bucket.begin() + i);
      return_value = value_copy;
      break;
    }
  }
  return return_value;
}

//**************************************************
// PrintHashTable function prints all the data 
// in hash table sequence.
//**************************************************
template <class T>
void HashTable<T>::PrintHashTable(void visit(T *)) {
  for (int i = 0; i < num_buckets; ++i) {
    // Display all items in this bucket.
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j].value) {
        visit(buckets[i][j].value);
      }
    }
  }
  for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
    visit(overflow_bucket[i].value);
  }
}

//**************************************************
// PrintStats function calculate and prints statastics 
// of Hash Table such as load factor, longest bucket, 
// number of full / empty buckets.
//**************************************************
template <class T>
void HashTable<T>::PrintStats() {
  int num_collision = 0;
  int max_bucket_size = 0; // Used to calculate longest branch
  int num_full_bucket = 0, num_empty_bucket = 0;
  // Iterate through all the buckets.
  for (int i = 0; i < num_buckets; ++i) {
    int total_elements = 0;
    // Iterate through each item in this bucket.
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j].value) {
        ++total_elements;
      }
    }
    if (total_elements > max_bucket_size) {
      max_bucket_size = total_elements;
    }
    if (total_elements > 1) {
      num_collision += total_elements;
    }
    if (total_elements == 0) {
      ++num_empty_bucket;
    }
    if (total_elements == 3) {
      ++num_full_bucket;
    }
  }
  for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
    ++num_collision;
  }
  if (num_collision > 0) {
    double load_factor = ((num_collision * 1.0) / num_buckets) * 100;
    cout << fixed << setprecision(2);
    cout << "Load Factor: " << load_factor << "%" << endl << endl;
  }

  // Finding longest branch in Hash Table
  cout << "Longest branch size is: " << max_bucket_size << endl;
  // Iterate through all the buckets.
  for (int i = 0; i < num_buckets; ++i) {
    int total_elements = 0;
    // Iterate through each item in this bucket.
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j].value) {
        ++total_elements;
      }
    }
    if (total_elements == max_bucket_size) {
      cout << "Longest Branch Home Adress: " << i << endl;
      for (int j = 0; j < max_bucket_size; ++j) {
        cout << "\tKey: " << buckets[i][j].key << endl;
      }
    }
  }
  cout << endl;
  cout << "Number of full buckets: " << num_full_bucket << endl << endl;
  cout << "Number of empty buckets: " << num_empty_bucket << endl << endl;
}

//**************************************************
// InsertValuesIntoVector function copies Hash Table
// data into a vector. 
//**************************************************
template <class T>
void HashTable<T>::InsertValuesIntoVector(vector<T*>* vec) {
  for (int i = 0; i < num_buckets; ++i) {
    // Display all items in this bucket.
    for (int j = 0; j < BUCKET_SIZE; ++j) {
      if (buckets[i][j].value) {
        vec->push_back(buckets[i][j].value);
      }
    }
  }
  for (unsigned int i = 0; i < overflow_bucket.size(); ++i) {
    vec->push_back(overflow_bucket[i].value);
  }
}
#endif
