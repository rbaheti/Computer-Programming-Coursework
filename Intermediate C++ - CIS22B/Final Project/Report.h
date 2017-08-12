#ifndef _REPORT_H_
#define _REPORT_H_
#include "Book.h"
#include "Inventory.h"
#include <vector>
#include <iostream>
using namespace std;

class Report {
public:
  Report(Inventory *inventory_object);

  // Base class destructor must be virtual.
  virtual ~Report();

  void PrintWholesaleValue();

  void PrintRetailValue();

  // Virtual method which will be overridden in the sub-classes(Report by Age, Cost and Quantity).
  // In this class Print() method prints all the books present in the Inventory.
  virtual void Print();

protected:
  Inventory *inventory;
  double totalCost = 0;
};

#endif