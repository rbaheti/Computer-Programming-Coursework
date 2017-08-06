// Specification file for the BST class
#ifndef BST_H
#define BST_H

using namespace std;

class BST
{
private:
    struct BST_Node
    {
        void     *data;    // The value in this node: a pointer to something
        BST_Node *left;    // To point to the left node
        BST_Node *right;   // To point to the right node
    } ;

    BST_Node *root;       // root of the tree
    int count;            // number of nodes in the tree
    int  (*compare) (void* argu1, void* argu2); // function pointer

public:
    // Constructor
    BST(int(*cmp) (void* argu1, void* argu2));

    // Destructor
    ~BST();

    // Binary Tree operations
    void BST_insert(void *data);
    void BST_InorderTraverse(void (*process) (void* dataPtr)) const;

private:
    void _BST_InorderTraverse( BST_Node *root, void (*process) (void* dataPtr) ) const;
    void _BST_Destroy(BST_Node *root);
};
#endif
