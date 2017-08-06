#include <iostream>
#include "Student.h"

using namespace std;

int main() {

  Student student[2];
  for (int i = 0; i < 2; i++) {
    student[i].getData();
  }

  for (int i = 0; i < 2; i++) {
    student[i].setData();
  }

  cin.get();
  cin.get();

  return 0;
}