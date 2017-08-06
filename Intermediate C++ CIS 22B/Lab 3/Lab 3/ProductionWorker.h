#ifndef _PRODUCTIONWORKER_H_
#define _PRODUCTIONWORKER_H_
#include "Employee.h"

class ProductionWorker : public Employee {
public:
  ProductionWorker();
  ProductionWorker(string name, long id, string date, int shift, double hourlyPayRate);

  void setProductionWorkerData(int shift, double hourlyPayRate);
  int GetProductionWorkerShift();
  double GetProductionWorkerPayRate();
  virtual string GetDesignation();

private:
  // Day shift is shift 1 and night shift is shift 2.
  int shift;
  double hourlyPayRate;
};




#endif
