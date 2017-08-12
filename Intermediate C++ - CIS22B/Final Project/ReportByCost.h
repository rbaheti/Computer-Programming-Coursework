#ifndef _REPORTBYCOST_H_
#define _REPORTBYCOST_H_
#include "Report.h"

class ReportByCost : public Report {
public:
  ReportByCost(Inventory *inventory_object);

  virtual void Print();
};

#endif