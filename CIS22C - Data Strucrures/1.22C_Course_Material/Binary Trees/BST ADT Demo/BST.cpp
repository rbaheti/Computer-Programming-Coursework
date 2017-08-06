// Implementation file for the BST class
#include <iostream>  // For cout and NULL

#include "BST.h"

using namespace std;

/**~*~*
   Constructor
*~**/
BST::BST(int  (*cmp) (void* argu1, void* argu2))
{
    root = NULL;
    count = 0;
    compare = cmp;
}

/**~*~*
   This function calls a recursive function to traverse the
   tree in inorder
*~**/
void BST::BST_InorderTraverse(void (*process) (void* data)) const
{
    _BST_InorderTraverse(root, process);
}

/**~*~*
   Inorder Traversal of the Binary Tree:
   Left-Root-Right
*~**/
void BST::_BST_InorderTraverse(BST_Node *root, void (*process) (void* data)) const
{
    if (root)
    {
        _BST_InorderTraverse(root->left, process);
        process(root->data);
        _BST_InorderTraverse(root->right, process);
    }
}

/**~*~*
   Insert data into a BST
*~**/
void BST::BST_insert(void *dataIn)
{
    BST_Node *newNode;
    BST_Node *pWalk;
    BST_Node *parent;

    // allocate the new node
    newNode = new BST_Node;
    newNode->data  = dataIn;
    newNode->left  = NULL;
    newNode->right = NULL;

    if (!root) // tree is empty
        root = newNode;
    else
    {
        pWalk = root;
        while( pWalk )
        {
            parent   = pWalk;
            if(compare(newNode->data, pWalk->data) < 0 )
                pWalk = pWalk->left;
            else
                pWalk = pWalk->right;
        }

        // insert the new node
        if( compare(newNode->data, parent->data) < 0 ) // no left child
             parent->left  = newNode;
        else
             parent->right = newNode;
    }

    count++;
}

/**~*~*
   Destructor
   This function calls a recursive function to delete all nodes in the binary tree
*~**/
BST::~BST()
{
    if (root)
        _BST_Destroy(root);
}

/**~*~*
   This function traverses the binary tree in postorder and deletes every node
*~**/
void BST::_BST_Destroy(BST_Node *root)
{
    if (root)
    {
        _BST_Destroy(root->left);
        _BST_Destroy(root->right);
        delete root;
    }
    return;
}

