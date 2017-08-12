#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include <fstream>
#include <memory> // for smart pointer (unique_ptr)
using namespace std;

#define INPUT_FILE "students.csv"

// Custom allocator for map so that it does not use our overloaded new/delete.
template <typename T>
class MallocAllocator {
public:
  typedef T value_type;
  MallocAllocator() {}
  template <typename U> MallocAllocator(const MallocAllocator<U>& other) {}
  T* allocate(size_t count)
  {
    return (T*)malloc(count * sizeof(T));
  }
  void deallocate(T* object, size_t n)
  {
    void* ptr = reinterpret_cast<void*>(object);
    free(ptr);
  }
};

class MemoryManager {
private:
  int numNewCalls;
  int numDeleteCalls;
  int numNewBytes;
  int numDeleteBytes;
  map<void*, int, less<void*>, MallocAllocator<int>> memAllocated;

public:
  MemoryManager() {
    numNewCalls = 0;
    numDeleteCalls = 0;
    numNewBytes = 0;
    numDeleteBytes = 0;
  }

  int GetNumNewCalls() { return numNewCalls; }
  int GetNumDeleteCalls() { return numDeleteCalls; }
  int GetNumNewBytes() { return numNewBytes; }
  int GetNumDeleteBytes() { return numDeleteBytes; }

  void Allocate(void* address, int bytes) {
    numNewBytes += bytes;
    ++numNewCalls;
    memAllocated[address] = bytes;
  }

  void Deallocate(void* address) {
    numDeleteBytes += memAllocated.at(address);
    ++numDeleteCalls;
  }
};

MemoryManager memoryManager;

class student {
private:
  unique_ptr<string> _firstname;
  unique_ptr<string> _lastname;
  unique_ptr<string> _course;
  unique_ptr<double> _gpa;

public:
  student() {}

  student(char* pc, char* pl, char* pf, char* pg) {
    _course.reset(new string(pc));
    _lastname.reset(new string(pl));
    _firstname.reset(new string(pf));
    _gpa.reset(new double(atof(pg)));
  }

  student(string* pitems) {
    _course.reset(new string(pitems[0]));
    _lastname.reset(new string(pitems[1]));
    _firstname.reset(new string(pitems[2]));
    _gpa.reset(new double(atof(pitems[3].c_str())));
  }
  student(const vector<string>& vs)
  {
    _course.reset(new string(vs[0]));
    _lastname.reset(new string(vs[1]));
    _firstname.reset(new string(vs[2]));
    _gpa.reset(new double(atof(vs[3].c_str())));
  }
  student(const student& s)
  {
    _course.reset(new string(*s._course));
    _lastname.reset(new string(*s._lastname));
    _firstname.reset(new string(*s._firstname));
    _gpa.reset(new double(*s._gpa));
  }
  ~student() {}

  string GetFirstName() { return *_firstname; }
  string GetLastName() { return *_lastname; }
  string GetCourseName() { return *_course; }
  double GetGpa() { return *_gpa; }
  operator double() { return *_gpa; }
  void student::operator = (const student& right) {
    _course.reset(new string(const_cast<student&>(right).GetCourseName()));
    _lastname.reset(new string(const_cast<student&>(right).GetLastName()));
    _firstname.reset(new string(const_cast<student&>(right).GetFirstName()));
    _gpa.reset(new double(const_cast<student&>(right).GetGpa()));
  }
  friend bool operator == (const student& left, const student& right)
  {
    string sl = *(left._course);
    string sr = *(right._course);
    int value = sl.compare(sr);
    return value == 0;
  }
  friend ostream& operator << (ostream& os, student& s)
  {
    os << s.GetCourseName();
    os << '\t';
    os << s.GetLastName();
    os << '\t';
    os << s.GetFirstName();
    os << '\t';
    os << s.GetGpa();
    return os;
  }

  // Overload new (Scalar new) operator
  void* operator new(size_t size){
  void* ptr = malloc(size);
  memoryManager.Allocate(ptr, size);
  return ptr;
  }

  // Overload delete (Scalar delete) operator
  void operator delete(void* ptr) {
    memoryManager.Deallocate(ptr);
    free(ptr);
  }

  // Overload new[] (Vector new) operator
  void* operator new[](size_t sz) {
    return operator new(sz);
  }

    // Overload delete[] (Vector delete) operator
    void operator delete[](void *ptr) {
    delete(ptr);
  }
};

vector<string> SplitLine(string line)
{
  vector<string> container;
  sregex_token_iterator end; // size is ZERO when created
  regex pattern("[^,]*");
  for (sregex_token_iterator pos(line.begin(), line.end(), pattern); pos != end; ++pos)
  {
    if ((*pos).length() > 0)
    {
      if ((static_cast<string>(*pos))[0] != 0x20) // 0x20 = BLANK
        container.push_back(*pos);
    }
  }
  return container;
}

// Read file 
void ReadStudentsFromFile(vector<unique_ptr<student>>& students_vec)  // pass students.csv
{
  ifstream inputFile;
  string line;
  // open the input file
  inputFile.open(INPUT_FILE);
  if (!inputFile) {
    cout << "Error opening file \"" << INPUT_FILE << "\"\n";
    exit(1);
  }
  
  while (!inputFile.eof()) {
    getline(inputFile, line);
    vector<string> info = SplitLine(line);
    student* student_details = new student(info);
    students_vec.push_back(unique_ptr<student>());
    students_vec.back().reset(student_details);
  }
}

int main() {
  {
    vector<unique_ptr<student>> students_vec;
    ReadStudentsFromFile(students_vec);
  }
  
  cout << "new() is called " << memoryManager.GetNumNewCalls() << " times" << endl << endl;
  cout << "Total number of bytes allocated by new(): " << memoryManager.GetNumNewBytes() << endl << endl;
  cout << "delete() is called " << memoryManager.GetNumDeleteCalls() << " times" << endl << endl;
  cout << "Total number of bytes deleted by delete(): " << memoryManager.GetNumDeleteBytes() << endl << endl;

  cin.get();
  return 0;
}