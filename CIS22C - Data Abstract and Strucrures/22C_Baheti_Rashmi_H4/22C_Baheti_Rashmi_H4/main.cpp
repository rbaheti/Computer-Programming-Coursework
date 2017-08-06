// Main test driver for BST
// Created by Frank M. Carrano and Tim Henry.
// Modified by Rashmi Baheti.

#include "BinarySearchTree.h"  // BST ADT 
#include "Student.h"
#include "Queue.h"
#include "Stack.h"
#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string>
using namespace std;

#define INPUT_FILE "gpa.txt"

// Function Prototypes:
void loadBinarySearchTree(BinarySearchTree<Student>* treePtr, const char *filename);
void displayInorderTree(BinarySearchTree<Student>* treePtr);
void requestAction(BinarySearchTree<Student>* treePtr);
void FindValue(BinarySearchTree<Student>* treePtr);
bool isNumber(string value);

// display function to pass to BST traverse functions
void displayIndented(Student &student) {
  cout << ". " << student.GetId() << endl;
}

// display function to pass to BST traverse functions
void displayStudentInfo(Student &student) {
  cout << student.GetId();
  cout << student.GetLastName() << ", ";
  cout << student.GetFirstName() << "; ";
  cout << student.GetGpa() << endl;
}

void check(bool success) {
  if (success)
    cout << "Done." << endl;
  else
    cout << " Entry not in tree." << endl;
}

int main()
{
  BinarySearchTree<Student> treePtr;
  loadBinarySearchTree(&treePtr, INPUT_FILE);
  requestAction(&treePtr);
  
  cin.get();
  return 0;
}

void requestAction(BinarySearchTree<Student>* treePtr) {
  cout << "T : Print tree as an indented list " << endl;
  cout << "S : Search by a unique key (student ID)" << endl;
  cout << "B : Tree Breadth-First Traversal" << endl;
  cout << "D : Depth-First Traversals: inorder, preorder, postorder" << endl;
  cout << "I : Iterative Depth - First Traversals : inorder, preorder, postorder" << endl;
  cout << "R : Find the longest branch and print it" << endl;
  cout << "H : Help – to show the menu" << endl;
  cout << "Q : Quit" << endl << endl;
  string choice = "T";

  while (choice != "Q" && choice != "q") {
    cout << "Please enter a letter to perform one of the menu operations: ";
    getline(cin, choice);
    cout << endl;
    if (choice == "T" || choice == "t" || choice == "S" || choice == "s" || choice == "B" || choice == "b" ||
      choice == "D" || choice == "d" || choice == "I" || choice == "i" || choice == "R" || choice == "r" ||
      choice == "A" || choice == "a" || choice == "H" || choice == "h" || choice == "Q" || choice == "q")
    {
      if (choice == "T" || choice == "t") {
        cout << "Tree as an indented list is: " << endl;
        treePtr->printIndented(displayIndented);
        cout << endl;
      }
      else if (choice == "S" || choice == "s") {
        FindValue(treePtr);
        cout << endl;
      }
      else if (choice == "B" || choice == "b") {
        cout << "Tree Breadth-First Traversal is: " << endl << endl;
        treePtr->breadthFisrtTraversal(displayStudentInfo);
        cout << endl;
      }
      else if (choice == "D" || choice == "d") {
        cout << "Depth First Traversal: " << endl << endl;
        cout << "1. In-Order Traversal: " << endl;
        treePtr->inOrder(displayStudentInfo);
        cout << endl;
        cout << "2. Pre-Order Traversal: " << endl;
        treePtr->preOrder(displayStudentInfo);
        cout << endl;
        cout << "3. Post-Order Traversal: " << endl;
        treePtr->postOrder(displayStudentInfo);
        cout << endl;
      }
      else if (choice == "I" || choice == "i") {
        cout << "Iterative Depth First Traversal: " << endl << endl;
        cout << "1. In-Order Traversal: " << endl;
        treePtr->IterativeInOrderTraversal(displayStudentInfo);
        cout << endl;
        cout << "2. Pre-Order Traversal: " << endl;
        treePtr->IterativePreOrderTraversal(displayStudentInfo);
        cout << endl;
        cout << "3. Post-Order Traversal: " << endl;
        treePtr->IterativePostOrderTraversal(displayStudentInfo);
        cout << endl;
      }
      else if (choice == "R" || choice == "r") {
        treePtr->longestBranch(displayStudentInfo);
        cout << endl;
      }
      else if (choice == "A" || choice == "a") {
        cout << "Developer: Rashmi Baheti" << endl;
      }
      else if (choice == "H" || choice == "h") {
        cout << "Please enter a letter to perform the following: " << endl;
        cout << "T : Print tree as an indented list " << endl;
        cout << "S : Search by a unique key (student ID)" << endl;
        cout << "B : Tree Breadth-First Traversal" << endl;
        cout << "D : Depth-First Traversals: inorder, preorder, postorder" << endl;
        cout << "I : Iterative Depth - First Traversals : inorder, preorder, postorder" << endl;
        cout << "R : Find the longest branch and print it" << endl;
        cout << "H : Help - to show the menu" << endl;
        cout << "Q : Quit" << endl;
      }
    }
    else {
      cout << "Please enter either T, S, B, D, I, R, H or Q" << endl;
    }
  }
  cout << "\nExiting now.. Good Bye!";
}

void loadBinarySearchTree(BinarySearchTree<Student>* treePtr, const char *filename) {
  ifstream inputDataFile;
  inputDataFile.open(filename);
  if (!inputDataFile) {
    cout << "File open failure!" << endl << endl;
    exit(1);
  }
  //Read each line of text into its own student object, then insert it into the BST
  int studentId;
  Student student;
  while (inputDataFile >> studentId) {
    student.SetId(studentId);

    //getline discards the delimiter ';' while preserving the space
    string lastName;
    getline(inputDataFile, lastName, ',');
    student.SetLastName(lastName);

    string firstName;
    getline(inputDataFile, firstName, ';');
    student.SetFirstName(firstName);

    float gpa;
    inputDataFile >> gpa;
    student.SetGpa(gpa);

    treePtr->insert(student);
  }
  inputDataFile.close();
}

void FindValue(BinarySearchTree<Student>* treePtr) {
  cout << "Please enter student ID you want to search: ";
  string inputId;
  getline(cin, inputId);
  if (!isNumber(inputId)) {
    cout << "Invalid entry. ID should be a positive integer." << endl;
    return;
  }
  int id = atoi(inputId.c_str());
  if (id <= 0) {
    cout << "Invalid entry. ID should be a positive integer." << endl;
    return;
  }
  Student s;
  s.SetId(id);
  bool ifFound = treePtr->getEntry(s);
  if (ifFound) {
    displayStudentInfo(s);
  }
  else {
    cout << "Student of ID number " << id << " was not found." << endl;
  }
}

bool isNumber(string value) {
  for (int i = 0; i < value.size(); ++i) {
    if (!isdigit(value.at(i))) {
      return false;
    }
  }
  return true;
}


/*********************************************************************
Sample Output:

T : Print tree as an indented list
S : Search by a unique key (student ID)
B : Tree Breadth-First Traversal
D : Depth-First Traversals: inorder, preorder, postorder
I : Iterative Depth - First Traversals : inorder, preorder, postorder
R : Find the longest branch and print it
H : Help û to show the menu
Q : Quit

Please enter a letter to perform one of the menu operations: t

Tree as an indented list is:
1. 3800
2. 4300
3. 5000
3. 3900
4. 4200
2. 3000
3. 3500
4. 3300
3. 1900
4. 2100
5. 2800
6. 2500
4. 1500

Please enter a letter to perform one of the menu operations: s

Please enter student ID you want to search: 5600
Student of ID number 5600 was not found.

Please enter a letter to perform one of the menu operations: s

Please enter student ID you want to search: 4300
4300 Trapp,  Amanda Elizabeth; 4

Please enter a letter to perform one of the menu operations: b

3800 Lee,  Victor; 2.8
3000 Brown,  Joanne; 4
4300 Trapp,  Amanda Elizabeth; 4
1900 Walljasper,  Bryan; 3.9
3500 Marcus,  John; 3.2
3900 Brown,  Joanne; 3.5
5000 Lee,  Lucy Marie; 3.4
1500 Marcus,  John; 4
2100 Andrews,  Dennis; 2.9
3300 Lee,  Victor; 3.6
4200 Brown,  Joanne; 4
2800 Brown,  Joanne; 2.6
2500 Lee,  Mary; 3.8

Please enter a letter to perform one of the menu operations: d

Depth First Traversal:

1. In-Order Traversal:
1500 Marcus,  John; 4
1900 Walljasper,  Bryan; 3.9
2100 Andrews,  Dennis; 2.9
2500 Lee,  Mary; 3.8
2800 Brown,  Joanne; 2.6
3000 Brown,  Joanne; 4
3300 Lee,  Victor; 3.6
3500 Marcus,  John; 3.2
3800 Lee,  Victor; 2.8
3900 Brown,  Joanne; 3.5
4200 Brown,  Joanne; 4
4300 Trapp,  Amanda Elizabeth; 4
5000 Lee,  Lucy Marie; 3.4

2. Pre-Order Traversal:
3800 Lee,  Victor; 2.8
3000 Brown,  Joanne; 4
1900 Walljasper,  Bryan; 3.9
1500 Marcus,  John; 4
2100 Andrews,  Dennis; 2.9
2800 Brown,  Joanne; 2.6
2500 Lee,  Mary; 3.8
3500 Marcus,  John; 3.2
3300 Lee,  Victor; 3.6
4300 Trapp,  Amanda Elizabeth; 4
3900 Brown,  Joanne; 3.5
4200 Brown,  Joanne; 4
5000 Lee,  Lucy Marie; 3.4

3. Post-Order Traversal:
1500 Marcus,  John; 4
2500 Lee,  Mary; 3.8
2800 Brown,  Joanne; 2.6
2100 Andrews,  Dennis; 2.9
1900 Walljasper,  Bryan; 3.9
3300 Lee,  Victor; 3.6
3500 Marcus,  John; 3.2
3000 Brown,  Joanne; 4
4200 Brown,  Joanne; 4
3900 Brown,  Joanne; 3.5
5000 Lee,  Lucy Marie; 3.4
4300 Trapp,  Amanda Elizabeth; 4
3800 Lee,  Victor; 2.8

Please enter a letter to perform one of the menu operations: i

Iterative Depth First Traversal:

1. In-Order Traversal:
1500 Marcus,  John; 4
1900 Walljasper,  Bryan; 3.9
2100 Andrews,  Dennis; 2.9
2500 Lee,  Mary; 3.8
2800 Brown,  Joanne; 2.6
3000 Brown,  Joanne; 4
3300 Lee,  Victor; 3.6
3500 Marcus,  John; 3.2
3800 Lee,  Victor; 2.8
3900 Brown,  Joanne; 3.5
4200 Brown,  Joanne; 4
4300 Trapp,  Amanda Elizabeth; 4
5000 Lee,  Lucy Marie; 3.4

2. Pre-Order Traversal:
3800 Lee,  Victor; 2.8
3000 Brown,  Joanne; 4
1900 Walljasper,  Bryan; 3.9
1500 Marcus,  John; 4
2100 Andrews,  Dennis; 2.9
2800 Brown,  Joanne; 2.6
2500 Lee,  Mary; 3.8
3500 Marcus,  John; 3.2
3300 Lee,  Victor; 3.6
4300 Trapp,  Amanda Elizabeth; 4
3900 Brown,  Joanne; 3.5
4200 Brown,  Joanne; 4
5000 Lee,  Lucy Marie; 3.4

3. Post-Order Traversal:
1500 Marcus,  John; 4
2500 Lee,  Mary; 3.8
2800 Brown,  Joanne; 2.6
2100 Andrews,  Dennis; 2.9
1900 Walljasper,  Bryan; 3.9
3300 Lee,  Victor; 3.6
3500 Marcus,  John; 3.2
3000 Brown,  Joanne; 4
4200 Brown,  Joanne; 4
3900 Brown,  Joanne; 3.5
5000 Lee,  Lucy Marie; 3.4
4300 Trapp,  Amanda Elizabeth; 4
3800 Lee,  Victor; 2.8

Please enter a letter to perform one of the menu operations: R

Longest Branch:
3800 Lee,  Victor; 2.8
3000 Brown,  Joanne; 4
1900 Walljasper,  Bryan; 3.9
2100 Andrews,  Dennis; 2.9
2800 Brown,  Joanne; 2.6
2500 Lee,  Mary; 3.8

Please enter a letter to perform one of the menu operations: a

Developer: Rashmi Baheti
Please enter a letter to perform one of the menu operations: H

Please enter a letter to perform the following:
T : Print tree as an indented list
S : Search by a unique key (student ID)
B : Tree Breadth-First Traversal
D : Depth-First Traversals: inorder, preorder, postorder
I : Iterative Depth - First Traversals : inorder, preorder, postorder
R : Find the longest branch and print it
H : Help - to show the menu
Q : Quit
Please enter a letter to perform one of the menu operations: g

Please enter either T, S, B, D, I, R, H or Q
Please enter a letter to perform one of the menu operations: w

Please enter either T, S, B, D, I, R, H or Q
Please enter a letter to perform one of the menu operations: q


Exiting now.. Good Bye!

************************************************************************/