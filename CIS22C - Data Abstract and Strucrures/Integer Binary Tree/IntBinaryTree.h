#ifndef INTBINARYTREE_H
#define INTBINARYTREE_H

class IntBinaryTree {
public:
  IntBinaryTree();
  ~IntBinaryTree();
  void InsertNode(int num);
  void DisplayInOrderTree();
  bool SearchNode(int);
  void DisplayPreOrderTree();
  void DisplayPostOrderTree();
  void DisplaySum();

private:
  struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
  };
  TreeNode* root;

  void RecursiveInsert(TreeNode *nodePtr, TreeNode *newNode);
  void DisplayInOrderTree(TreeNode*);
  void DisplayPreOrderTree(TreeNode*);
  void DisplayPostOrderTree(TreeNode*);
  int TreeSum(TreeNode* node);
};






#endif
