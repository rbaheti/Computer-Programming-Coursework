#ifndef BST_H_
#define BST_H_

#include<string>
using namespace std;

class BST {
public:
  BST() {
    root = NULL;
  }
  ~BST();
  void insert() { _insert(root); }


private:
  struct TreeNode {
    int value;
    TreeNode* right;
    TreeNode* left;
  };
  TreeNode* root;
  void _insert(TreeNode*);
  void _search(TreeNode*);
  void _deleteNode(TreeNode*);
  void _destroyTree(TreeNode*);
  void _displayInorder(TreeNode*);
  void _displayPreorder(TreeNode*);
  void _displayPostorder(TreeNode*);
};
#endif

