#include "IntBinaryTree.h"
#include <string>
#include <iostream>
using namespace std;

IntBinaryTree::IntBinaryTree() {
  root = NULL;
}

IntBinaryTree::~IntBinaryTree() {

}

void IntBinaryTree::InsertNode(int num) {
  TreeNode *newNode = new TreeNode;
  newNode->value = num;
  newNode->left = NULL;
  newNode->right = NULL;

  if (root == NULL) {
    root = newNode;
    return;
  }
  RecursiveInsert(root, newNode);
}

void IntBinaryTree::RecursiveInsert(TreeNode *nodePtr, TreeNode *newNode) {
  if (nodePtr->value < newNode->value) {
    if (nodePtr->right) {
      RecursiveInsert(nodePtr->right, newNode);
    }
    else {
      nodePtr->right = newNode;
    }
  }
  else {
    if (nodePtr->left) {
      RecursiveInsert(nodePtr->left, newNode);
    }
    else {
      nodePtr->left = newNode;
    }
  }
}

void IntBinaryTree::DisplayInOrderTree(TreeNode* node) {
  if (node != NULL) {
    DisplayInOrderTree(node->left);
    cout << node->value << endl;
    DisplayInOrderTree(node->right);
  }
}

int IntBinaryTree::TreeSum(TreeNode* node) {
  int sum = 0;
  if (node == NULL) {
    return 0;
  }
  if (node != NULL) {
    sum += TreeSum(node->left);
    sum += node->value;
    sum += TreeSum(node->right);
    return sum;
  }
}

void IntBinaryTree::DisplaySum() {
  cout << "Sum of tree is: " << TreeSum(root) << endl;
}

void IntBinaryTree::DisplayInOrderTree() {
  cout << "Tree's In-Order list is: " << endl;
  DisplayInOrderTree(root);
  cout << endl;
}

void IntBinaryTree::DisplayPreOrderTree(TreeNode* node) {
  if (node != NULL) {
    cout << node->value << endl;
    DisplayPreOrderTree(node->left);
    DisplayPreOrderTree(node->right);
  }
}

void IntBinaryTree::DisplayPreOrderTree() {
  cout << "Tree's Pre-Order list is: " << endl;
  DisplayPreOrderTree(root);
  cout << endl;
}

void IntBinaryTree::DisplayPostOrderTree(TreeNode* node) {
  if (node != NULL) {
    DisplayPostOrderTree(node->left);
    DisplayPostOrderTree(node->right);
    cout << node->value << endl;
  }
}

void IntBinaryTree::DisplayPostOrderTree() {
  cout << "Tree's Post-Order list is: " << endl;
  DisplayPostOrderTree(root);
  cout << endl;
}

bool IntBinaryTree::SearchNode(int num) {
  TreeNode *nodePtr = root;
  while (nodePtr) {
    if (nodePtr->value == num) {
      return true;
    }
    else if (num < nodePtr->value) {
      nodePtr = nodePtr->left;
    }
    else
      nodePtr = nodePtr->right;
  }
  return false;
}

