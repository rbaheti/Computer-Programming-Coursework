#include"Country.h"

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
