#ifndef _REPORTBYQUANTITY_H_
#define _REPORTBYQUANTITY_H_
#include "Report.h"

class ReportByQuantity : public Report {
public:
  ReportByQuantity(Inventory *inventory_object);

  virtual void Print();
};

#endif