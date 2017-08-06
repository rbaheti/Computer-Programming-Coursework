#include <string>
using namespace std;

class Student {
public:
  Student();

private:
  string firstName;
  string lastName;
  int id;
  int age;

public:
  void getData();
  void setData();
};
