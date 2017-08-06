#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "Student.h"

class BinarySearchTree {
private:
  struct TreeNode {
    Student student;
    TreeNode *left;
    TreeNode *right;
  };
  TreeNode *root;
  void insert();

public:

};


#endif
