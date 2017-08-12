#ifndef _REPORTBYAGE_H_
#define _REPORTBYAGE_H_
#include "Report.h"

class ReportByAge : public Report {
public:
  ReportByAge(Inventory *inventory_object);

  virtual void Print();
};

#endif