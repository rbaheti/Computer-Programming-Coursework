// Specification file for the Country class
#ifndef COUNTRY_H
#define COUNTRY_H

#include <string> 
using namespace std; // to replace std::string with simple string

class Country
{
public:
  Country();
  ~Country();
  void SetCode(const char *code);
  void SetName(string name);
  void SetCapital(string capital);
  void SetPopulation(int population);
  const char* GetCode();
  string GetName();
  string GetCapital();
  int GetPopulation();

private:
  char code[3]; // 2 + 1 for '\0'
  string name;
  string capital;
  int population;
};
#endif
