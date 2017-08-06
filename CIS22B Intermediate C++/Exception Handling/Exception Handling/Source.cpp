#include <iostream>
#include <string>
using namespace std;

int ReadIntegerInput(int startValue, int endValue) {
  string choice;
  cout << "Please enter your choice " << startValue << " through " << endValue << ": ";
  cin >> choice;
  cin.ignore(9999999999999, '\n');
  // atoi returns 0 when the conversion of string to integer is not possible due to invalid input.
  int intChoice = atoi(choice.c_str());
  if (intChoice < startValue || intChoice > endValue) {
    throw "Error: Invalid entry. Please try again.\n";
  }
  else {
    cout << "You entered a valid number!" << endl;
  }
    return intChoice;
}

int main() {
  bool tryAgain = true;
  while (tryAgain) {
    try {
      cout << "You entered: " << ReadIntegerInput(1, 4);
      tryAgain = false;
    }
    catch (char *e) {
      cout << e;
    }
  }

  cin.get();
  cin.get();
  return 0;
}