#include <iostream>
#include <string>
using namespace std;

int main() {
  string str = "10051499";
  cout << "String: " << str << endl;
  string  str2 = str.substr(2, 4);
  cout << "Substring: " << str2  << endl;
  const char *cstr = str2.c_str();
  int month = atoi(cstr);
  cout << "Digits: " << month;

  cin.get();
  cin.get();
  return 0;
}