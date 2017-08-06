#include "ShiftSupervisor.h"
#include <iostream>

// Default constructor initializes member varialbles to 0.
ShiftSupervisor::ShiftSupervisor() {
  annualSalary = 0;
  annualProdBonus = 0;
}

ShiftSupervisor::ShiftSupervisor(string name, long id, string date, double annualSalary, double annualProdBonus)
  : Employee(name, id, date) {
  this->annualSalary = annualSalary;
  this->annualProdBonus = annualProdBonus;
}

void ShiftSupervisor::SetShiftSupervisorData(double salary, double bonus) {
  annualSalary = salary;
  annualProdBonus = bonus;
}

double ShiftSupervisor::GetAnnualSalary() {
  return annualSalary;
}

double ShiftSupervisor::GetProdBonus() {
  return annualProdBonus;
}

string ShiftSupervisor::GetDesignation() {
  return "Shift Supervisor";
}