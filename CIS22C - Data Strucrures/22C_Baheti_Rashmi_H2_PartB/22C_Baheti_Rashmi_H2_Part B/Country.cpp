#define _CRT_SECURE_NO_WARNINGS
#include"Country.h"
#include <iostream>
#include <iomanip>

using namespace std;

string formattedPopulation(int population) {
  string stringPopulation;
  while (population != 0) {
    int modulo = (population % 1000);
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

Country::Country() {
  code[0] = '\0';
  code[1] = '\0';
  code[2] = '\0';

  population = 0;
}

Country::~Country() {
}

void Country::SetCode(const char *code) {
  this->code[0] = code[0];
  this->code[1] = code[1];
  this->code[2] = '\0';
}

void Country::SetName(string name) {
  this->name = name;
}

void Country::SetCapital(string capital) {
  this->capital = capital;
}
void Country::SetPopulation(int population) {
  this->population = population;
}
const char* Country::GetCode() {
  return code;
}
string Country::GetName() {
  return name;
}
string Country::GetCapital() {
  return capital;
}
int Country::GetPopulation() {
  return population;
}

ostream& operator<<(ostream& os, Country& country) {
  os << left << setw(5) << country.GetCode() << " ";
  os << left << setw(20) << country.GetName();
  os << left << setw(20) << country.GetCapital();
  os << right << setw(15) << formattedPopulation(country.GetPopulation());
  return os;
}

bool Country::operator==(Country& rhs) {
  return (strcmp(code, rhs.GetCode()) == 0);
}

bool Country::operator<(Country& rhs) {
  return (strcmp(code, rhs.GetCode()) < 0);
}