// Class that encapsulates all the information related to a student
// Created by Rashmi Baheti.

#ifndef _STUDENT_H
#define _STUDENT_H
#include <string>
using namespace std;

class Student {
private:
  int id;
  string lastName;
  string firstName;
  float gpa;

public:
  // Constructor
  Student();
  // Destructor
  ~Student();

  // Mutators
  void SetId(int id) { this->id = id; }
  void SetLastName(string lastName) { this->lastName = lastName; }
  void SetFirstName(string firstName) { this->firstName = firstName; }
  void SetGpa(float gpa) { this->gpa = gpa; }
  // Accessors
  int GetId() const { return id; }
  string GetLastName() const { return lastName; }
  string GetFirstName() const { return firstName; }
  float GetGpa() const { return gpa; }

  bool operator==(const Student& rhs);
  bool operator<(const Student& rhs);
  bool operator>(const Student& rhs);
  const Student operator=(const Student& rhs);
};

// Overloaded << operator needs to be declared global.
ostream& operator<<(ostream& os, Student& student);

#endif
