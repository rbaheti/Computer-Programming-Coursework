#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& values) {
  for (int i = 0; i < values.size(); ++i) {
    cout << values[i] << " ";
  }
  cout << endl;
}

void RegularInsertionSort(vector<int>& values) {
  for (int i = 1; i < values.size(); i += 1) {
    int j = i - 1;
    int key_to_insert = values[i];

    // Now insert key_to_insert in its right place in the sorted range [0, i - 1].
    while (j >= 0 && key_to_insert < values[j]) {
      // Keep shifting values to the right until the values are greater than key_to_insert.
      values[j + 1] = values[j];
      j -= 1;
    }
    // j + 1 is the slot where key_to_insert should be set. After this, range [0, i] will become sorted.
    values[j + 1] = key_to_insert;
  }
}

void InsertionSortForShellSort(vector<int>& values, int gap) {
  for (int sublist_no = 0; sublist_no < gap; ++sublist_no) {
    for (int i = sublist_no + gap; i < values.size(); i += gap) {
      if (i >= values.size()) continue;

      int j = i - gap;
      int key_to_insert = values[i];

      // Now insert key_to_insert in its right place in the sorted range of current sublist.
      while (j >= 0 && key_to_insert < values[j]) {
        // Keep shifting values to the right until the values are greater than key_to_insert.
        values[j + gap] = values[j];
        j -= gap;
      }
      // j + gap is the slot where key_to_insert should be set.
      values[j + gap] = key_to_insert;
    }
  }
}

void ShellSort(vector<int>& values) {
  for (int gap = values.size() / 2; gap >= 1; gap /= 2) {
    InsertionSortForShellSort(values, gap);

    cout << "Vector afer one run: " << endl;
    PrintVector(values);
  }
}

void MergeSort(vector<int>& values) {
  if (values.size() <= 1) return;

  // Partition the list into 2 and sort the 2 partitions.
  int mid = values.size() / 2;
  
  vector<int> first_partition, second_partition;
  first_partition.assign(values.begin(), values.begin() + mid);
  second_partition.assign(values.begin() + mid, values.end());
  MergeSort(first_partition);
  MergeSort(second_partition);

  // Now merge the 2 sorted partitions.
  int next_index_in_first_partition = 0;
  int next_index_in_second_partition = 0;
  int next_index_in_output_vector = 0;
  while (true) {
    if (next_index_in_first_partition < first_partition.size() &&
      next_index_in_second_partition < second_partition.size()) {
      // Find the minimum from the 2 partitions and put it in output vector.
      if (first_partition[next_index_in_first_partition] <
        second_partition[next_index_in_second_partition]) {
        values[next_index_in_output_vector] = first_partition[next_index_in_first_partition];
        ++next_index_in_output_vector;
        ++next_index_in_first_partition;
      }
      else {
        values[next_index_in_output_vector] = second_partition[next_index_in_second_partition];
        ++next_index_in_output_vector;
        ++next_index_in_second_partition;
      }
    }
    else if (next_index_in_first_partition < first_partition.size()) {
      // Only values in first_partition need to be put in the output vector now.
      values[next_index_in_output_vector] = first_partition[next_index_in_first_partition];
      ++next_index_in_output_vector;
      ++next_index_in_first_partition;
    }
    else if (next_index_in_second_partition < second_partition.size()) {
      // Only values in second_partition need to be put in the output vector now.
      values[next_index_in_output_vector] = second_partition[next_index_in_second_partition];
      ++next_index_in_output_vector;
      ++next_index_in_second_partition;
    }
    else {
      break;
    }
  }
}

int QuickSortPartition(vector<int>& values, int low, int high) {
  int pivot = values[high];

  // After the [low, high] range is partitioned, pivot will be at
  // values[partition_index]
  int partition_index = high;
  int i = low;
  while(i < partition_index) {
    if (values[i] >= pivot) {
      // Move this greater value to the beginning of right partition.
      values[partition_index] = values[i];
      
      --partition_index;
      values[i] = values[partition_index];
    }
    else {
      ++i;
    }
  }
  values[partition_index] = pivot;
  return partition_index;
}

void QuickSort(vector<int>& values, int low, int high) {
  if ((high - low) <= 0) return;

  int partition_index = QuickSortPartition(values, low, high);
  // Call QuickSort for left partition
  QuickSort(values, low, partition_index - 1);
  // Call QuickSort for right partition
  QuickSort(values, partition_index + 1, high);
}

int main() {
  int num_values;
  cout << "Enter number of values in the vector: ";
  cin >> num_values;

  vector<int> values;
  for (int i = 0; i < num_values; ++i) {
    cout << "Enter value#" << i + 1 << ": ";
    int value;
    cin >> value;
    values.push_back(value);
  }

  QuickSort(values, 0, values.size() - 1);
  cout << "Sorted vector is: " << endl;
  PrintVector(values);

  cin.get();
  cin.get();
  return 0;
}