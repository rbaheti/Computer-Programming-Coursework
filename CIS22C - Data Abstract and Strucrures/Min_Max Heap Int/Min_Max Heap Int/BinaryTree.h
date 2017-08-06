// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Rashmi Baheti

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <string>
using namespace std;

template<class ItemType>
class BinaryTree
{
protected:
  BinaryNode<ItemType>* rootPtr;		// ptr to root node
  int count;							// number of nodes in tree

public:
  // "admin" functions
  BinaryTree() { rootPtr = NULL; count = 0; }    // constructor
  BinaryTree(const BinaryTree<ItemType> & tree) { } // parameterized constructor
  virtual ~BinaryTree() { clear(); }
  BinaryTree & operator = (const BinaryTree & sourceTree);

  // common functions for all binary trees
  bool isEmpty() const { return count == 0; }
  int size() const { return count; }
  void clear() { destroyTree(rootPtr); rootPtr = NULL; count = 0; }
  void preOrder(void visit(ItemType &)) const { _preorder(visit, rootPtr); }
  void inOrder(void visit(ItemType &)) const { _inorder(visit, rootPtr); }
  void postOrder(void visit(ItemType &)) const { _postorder(visit, rootPtr); }

  // abstract functions to be implemented by derived class
  virtual bool insert(const ItemType & newData) = 0;
  virtual bool remove(const ItemType & data) = 0;
  virtual bool getEntry(ItemType & anEntry) const = 0;

private:
  // delete all nodes from the tree
  void destroyTree(BinaryNode<ItemType>* nodePtr);

  // copy from the tree rooted at nodePtr and returns a pointer to the copy
  BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

  // internal traverse
  void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
  void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
  void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
};

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
  BinaryNode<ItemType>* newNodePtr = NULL;
  if (nodePtr) {
    newNodePtr = nodePtr;
  }
  if (nodePtr->getLeftPtr()) {
    newNodePtr->setLeftPtr(nodePtr->getLeftPtr());
    copyTree(nodePtr->getLeftPtr());
  }
  if (nodePtr->getRightPtr()) {
    // newNodePtr->setRightPtr(nodePtr->getRightPtr());
    copyTree(nodePtr->getRightPtr());
  }
  return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
  if (nodePtr == NULL) {
    return;
  }
  if (nodePtr->getLeftPtr()) {
    destroyTree(nodePtr->getLeftPtr());
  }
  if (nodePtr->getRightPtr()) {
    destroyTree(nodePtr->getRightPtr());
  }
  delete nodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
  if (nodePtr != NULL)
  {
    ItemType item = nodePtr->getItem();
    visit(item);
    _preorder(visit, nodePtr->getLeftPtr());
    _preorder(visit, nodePtr->getRightPtr());
  }
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
  if (nodePtr != NULL)
  {
    ItemType item = nodePtr->getItem();
    _inorder(visit, nodePtr->getLeftPtr());
    visit(item);
    _inorder(visit, nodePtr->getRightPtr());
  }
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
  if (nodePtr != NULL)
  {
    ItemType item = nodePtr->getItem();
    _postorder(visit, nodePtr->getLeftPtr());
    _postorder(visit, nodePtr->getRightPtr());
    visit(item);
  }
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
  clear();
  rootPtr = copyTree(sourceTree.rootPtr);
  return *this;
}
#endif