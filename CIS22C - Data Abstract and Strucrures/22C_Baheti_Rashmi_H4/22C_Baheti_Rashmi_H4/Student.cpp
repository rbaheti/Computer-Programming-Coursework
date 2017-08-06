// Class that encapsulates all the information related to a student
// Created by Rashmi Baheti.
#include "Student.h"

Student::Student() {
  id = 0000;
  gpa = 0.0;
}

Student::~Student() {
}

bool Student::operator==(const Student& rhs) {
  return id == rhs.GetId();
}

bool Student::operator<(const Student& rhs) {
  return id < rhs.GetId();
}

bool Student::operator>(const Student& rhs) {
  return (id > rhs.GetId());
}

const Student Student::operator=(const Student& rhs) {
  id = rhs.GetId();
  lastName = rhs.GetLastName();
  firstName = rhs.GetFirstName();
  gpa = rhs.GetGpa();
  return *this;
}

ostream& operator<<(ostream& os, Student& student) {
  os << student.GetId() << " ";
  return os;
}