#include <iostream>
#include <fstream>
using namespace std;

int main() {
  cout << "Please open file.txt file.";
  fstream dataFile;
  dataFile.open("file.txt", ios::in | ios::out);

  cin.get();
  return 0;
}