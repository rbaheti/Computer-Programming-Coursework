#include "Employee.h"
#include <iostream>

// The constructor intializes Employee attributes to NULL and 0;
Employee::Employee() {
  empName = "";
  empNum = 0;
  empHireDate = "";
}

Employee::Employee(string name, long id, string date) {
  empName = name;
  empNum = id;
  empHireDate = date;
}

void Employee::SetEmployeeData(string name, long id, string date) {
  empName = name;
  empNum = id;
  empHireDate = date;
}

string Employee::GetEmployeeName() {
  return empName;
}

long Employee::GetEmployeeNum() {
  return empNum;
}

string Employee::GetEmployeeHireDate() {
  return empHireDate;
}

string Employee::GetDesignation() {
  return "Employee";
}