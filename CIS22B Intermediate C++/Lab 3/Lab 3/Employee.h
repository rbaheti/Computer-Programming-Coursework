#ifndef _EMPLOYEE_H_
#define _EMPLOYEE_H_
#include <string>
using namespace std;

class Employee {
private:
  string empName;
  long empNum;
  string empHireDate;

public:
  Employee();
  Employee(string name, long id, string date);
  void SetEmployeeData(string name, long id, string date);
  string GetEmployeeName();
  long GetEmployeeNum();
  string GetEmployeeHireDate();
  virtual string GetDesignation();
};

#endif