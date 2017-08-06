#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

string formattedPopulation(int population) {
  string stringPopulation;
  while (population != 0) {
    int modulo = (population % 1000);
    cout << "Modulo value: " << modulo << endl;
    population = population / 1000;
    
    char modulo_str[4] = "000";
    if (population != 0) {
      // Pad modulo with zeroes in the beginning if it does not have 3 digits in it.
      int temp_modulo = modulo / 10;
      int num_digits = 1;
      while (temp_modulo) {
        num_digits++;
        temp_modulo /= 10;
      }
      _itoa(modulo, modulo_str + 3 - num_digits, 10);
    }
    else {
      _itoa(modulo, modulo_str, 10);
    }

    if (stringPopulation.empty()) {
      stringPopulation = modulo_str;
    }
    else {
      stringPopulation = modulo_str + string(",") + stringPopulation;
    }
  }
  return stringPopulation;
}

int main() {
  cout << formattedPopulation(32805000);

  cin.get();
  return 0;
}