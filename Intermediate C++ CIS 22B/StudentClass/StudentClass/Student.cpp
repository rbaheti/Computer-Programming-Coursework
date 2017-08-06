#include "Student.h"
#include <iostream>

Student::Student() {}

void Student::getData() {
  cout << "Please enter Student's first name: ";
  cin >> firstName;

  cout << "Please enter Student's last name: ";
  cin >> lastName;

  cout << "Enter Student's ID: ";
  cin >> id;

  cout << "Enter Student's age: ";
  cin >> age;
}

void Student::setData() {
  cout << "Here is the student's data: " << endl;
  cout << "Name: " << firstName << " " << lastName << endl;
  cout << "ID: " << id << endl;
  cout << "Age: " << age << endl;
}