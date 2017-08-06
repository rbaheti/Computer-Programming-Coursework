#ifndef _SHIFTSUPERVISOR_H_
#define _SHIFTSUPERVISOR_H_
#include "Employee.h"

class ShiftSupervisor : public Employee {
public:
  ShiftSupervisor();
  ShiftSupervisor(string name, long id, string date, double annualSalary, double annualProdBonus);
  void SetShiftSupervisorData(double salary, double bonus);
  double GetAnnualSalary();
  double GetProdBonus();
  virtual string GetDesignation();

private:
  double annualSalary;
  double annualProdBonus;
};

#endif