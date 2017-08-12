#include <iostream>
#include <iomanip>
using namespace std;

// Template function for finding Minimum of the two numbers eneterd by the user.
template <class T>
T Minimun(T var1, T var2) {
  if (var1 < var2)
    return var1;
  else
    return var2;
}

// Template function for finding Maximum of the two numbers eneterd by the user.
template <class T>
T Maximun(T var1, T var2) {
  if (var1 > var2)
    return var1;
  else
    return var2;
}

// Template function for finding Absolute Value of the number eneterd by the user.
template <class T>
T AbsoluteValue(T value) {
  if (value < 0) {
    return (value * -1);
  }
  else return value;
}

// Template function for finding total of the numbers entered by the user.
template <class T>
T Total(int num) {
  T total = 0;
  T value;
  cout << "Please enter your value: ";
  cin >> value;
  for (T i = 0; i < num; ++i) {
    total += value;
    if (i >= num - 1) {
      break;
    }
    cout << "Please enter your value: ";
    cin >> value;
  }
  return total;
}

int main() {
  // Demonstrating Minimum/Maximum templates using different types of inputs.
  // 1. Using Integer input:
  int userInt1, userInt2;
  cout << "Please enter two integers to find the minimum and maximum of the two: " << endl;
  cout << "Integer 1: ";
  cin >> userInt1;
  cout << "Integer 2: ";
  cin >> userInt2;
  cout << "Minimum value is: " << Minimun(userInt1, userInt2) << endl;
  cout << "Maximum value is: " << Maximun(userInt1, userInt2) << endl << endl;

  // 2. Using Double input:
  double userDouble1, userDouble2;
  cout << setprecision(2) << fixed;
  cout << "Please enter two whole numbers to find the minimum and maximum of the two: " << endl;
  cout << "Whole number 1: ";
  cin >> userDouble1;
  cout << "Whole number 2: ";
  cin >> userDouble2;
  cout << "Minimum value is: " << Minimun(userDouble1, userDouble2) << endl;
  cout << "Maximum value is: " << Maximun(userDouble1, userDouble2) << endl << endl;

  // 3. Using Character input:
  char userChar1, userChar2;
  cout << "Please enter two characters to find the minimum and maximum of the two: " << endl;
  cout << "Character 1: ";
  cin >> userChar1;
  cout << "Character 2: ";
  cin >> userChar2;
  cout << "Minimum value is: " << Minimun(userChar1, userChar2) << endl;
  cout << "Maximum value is: " << Maximun(userChar1, userChar2) << endl << endl;


  // Demonstrating Absolute Value template using different types of inputs.
  // 1. Using Integer input:
  int userInt;
  cout << "Please enter an integer to find its absolute value: ";
  cin >> userInt;
  cout << "The absolute value of " << userInt << " is " << AbsoluteValue(userInt);
  cout << endl << endl;

  // 2. Using Double input:
  double userDouble;
  cout << setprecision(2) << fixed;
  cout << "Please enter a whole number to find its absolute value: ";
  cin >> userDouble;
  cout << "The absolute value of " << userDouble << " is " << AbsoluteValue(userDouble);
  cout << endl << endl;

  // Demonstrating Total template using different types of inputs.
  // 1. Using Integer input:
  int userNum;
  cout << "Calculating sum of integers: " << endl;
  cout << "Please enter total number of integers you want to add: ";
  cin >> userNum;
  // Since the function Total() is templatized only for its return type and not for its parameter,
  // we need to explicitly specify that we want to call Total() for integer type.
  cout << "Sum of integers is: " << Total<int>(userNum);
  cout << endl << endl;

  // 2. Using Double input:
  cout << setprecision(2) << fixed;
  cout << "Calculating sum of whole numbers: " << endl;
  cout << "Please enter total number of whole numbers you want to add: ";
  cin >> userNum;
  // Since the function Total() is templatized only for its return type and not for its parameter,
  // we need to explicitly specify that we want to call Total() for Double type.
  cout << "Sum of whole numbers is: " << Total<double>(userNum);
  cout << endl << endl;

  cout << "End of program.";

  cin.get();
  cin.get();

  return 0;
}