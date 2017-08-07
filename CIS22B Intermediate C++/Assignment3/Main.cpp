#include <iostream>
#include <string>
#include "ProductionWorker.h"
#include "ShiftSupervisor.h"
#include "TeamLeader.h"
using namespace std;

int main() {
  string name, hireDate;
  long empNum;
  int shift;
  double payRate;
  ProductionWorker productionWorker;

  cout << "Please enter Production Worker's details: " << endl;
  cout << "Name: ";
  getline(cin, name);
  cout << "Number: ";
  cin >> empNum;
  cin.get();
  cout << "Hire Date: ";
  getline(cin, hireDate);
  cout << "Day Shift or Night Shift ?" << endl;
  cout << "Press 1 for Day Shift and 2 for Night Shift: ";
  cin >> shift;
  cout << "Hourly Pay Rate($): ";
  cin >> payRate;

  productionWorker.SetEmployeeData(name, empNum, hireDate);
  productionWorker.setProductionWorkerData(shift, payRate);

  cout << endl;
  cout << "Production Worker " << productionWorker.GetEmployeeName() << "'s information:" << endl;
  cout << "Name: " << productionWorker.GetEmployeeName() << endl;
  cout << "Id: " << productionWorker.GetEmployeeNum() << endl;
  cout << "Hire Date: " << productionWorker.GetEmployeeHireDate() << endl;
  cout << "Shift: " << productionWorker.GetProductionWorkerShift() << endl;
  cout << "Hourly Pay Rate: $" << productionWorker.GetProductionWorkerPayRate() << endl;

  double annShiftSalary;
  double annShiftProdBonus;
  cout << endl;
  cout << "Please enter Shift Supervisor's details: " << endl;
  cin.get();
  cout << "Name: ";
  getline(cin, name);
  cout << "Number: ";
  cin >> empNum;
  cin.get();
  cout << "Hire Date: ";
  getline(cin, hireDate);
  cout << "Annual Salary($): ";
  cin >> annShiftSalary;
  cout << "Annual Production Bonus($): ";
  cin >> annShiftProdBonus;

  ShiftSupervisor shiftSupervisor(name, empNum, hireDate, annShiftSalary, annShiftProdBonus);

  cout << endl;
  cout << "Shift Supervisor " << shiftSupervisor.GetEmployeeName() << "'s information:" << endl;
  cout << "Name: " << shiftSupervisor.GetEmployeeName() << endl;
  cout << "Id: " << shiftSupervisor.GetEmployeeNum() << endl;
  cout << "Hire Date: " << shiftSupervisor.GetEmployeeHireDate() << endl;
  cout << "Annual Salary: $" << shiftSupervisor.GetAnnualSalary() << endl;
  cout << "Annual Production Bonus: $" << shiftSupervisor.GetProdBonus() << endl;

  double TLMonthlyBonus;
  double TLRequiredWorkingHours;
  double TLAttendedWorkingHours;


  cout << endl;
  cout << "Please enter Team Leader's details: " << endl;
  cin.get();
  cout << "Name: ";
  getline(cin, name);
  cout << "Number: ";
  cin >> empNum;
  cin.get();
  cout << "Hire Date: ";
  getline(cin, hireDate);
  cout << "Day Shift or Night Shift ?" << endl;
  cout << "Press 1 for Day Shift and 2 for Night Shift: ";
  cin >> shift;
  cout << "Hourly Pay Rate($): ";
  cin >> payRate;
  cout << "Monthly Bonus($): ";
  cin >> TLMonthlyBonus;
  cout << "Required Working Hours: ";
  cin >> TLRequiredWorkingHours;
  cout << "Attended Working Hours: ";
  cin >> TLAttendedWorkingHours;

  TeamLeader teamLeader(name, empNum, hireDate, shift, payRate,
    TLMonthlyBonus, TLRequiredWorkingHours, TLAttendedWorkingHours);

  cout << endl;
  cout << "Team Leader " << teamLeader.GetEmployeeName() << "'s information:" << endl;
  cout << "Name: " << teamLeader.GetEmployeeName() << endl;
  cout << "Id: " << teamLeader.GetEmployeeNum() << endl;
  cout << "Hire Date: " << teamLeader.GetEmployeeHireDate() << endl;
  cout << "Shift: " << teamLeader.GetProductionWorkerShift() << endl;
  cout << "Hourly Pay Rate: $" << teamLeader.GetProductionWorkerPayRate() << endl;
  cout << "Monthly Bonus($): " << teamLeader.GetMonthlyBonus() << endl;
  cout << "Required Working Hours: " << teamLeader.GetRequiredWorkingHours() << endl;
  cout << "Attended Working Hours: " << teamLeader.GetAttendedWorkingHours() << endl << endl;

  // Static binding example
  Employee employee_1 = teamLeader;
  cout << "TeamLeader's designation (using static binding): " << employee_1.GetDesignation() << endl << endl;

  // Dynamic binding example
  Employee *employee_2 = new TeamLeader(name, empNum, hireDate, shift, payRate,
    TLMonthlyBonus, TLRequiredWorkingHours, TLAttendedWorkingHours);
  cout << "TeamLeader's designation (using dynamic binding): " << employee_2->GetDesignation() << endl;
  delete employee_2;

  cin.get();
  cin.get();

  return 0;
}