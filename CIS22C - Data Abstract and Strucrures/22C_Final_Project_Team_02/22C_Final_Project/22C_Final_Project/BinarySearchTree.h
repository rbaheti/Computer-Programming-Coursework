#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <algorithm>
#include "BinaryTree.h"
#include "Queue.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
  typedef int (*ComparatorFunc)(ItemType *, ItemType *);
  ComparatorFunc comparator;

  // internal insert node: insert newNode in nodePtr subtree
  BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);

  // internal remove node: locate and delete target node under nodePtr subtree
  BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType* target, bool& success);

  // delete target node from tree, called by internal remove node
  BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

  // remove the leftmost node in the left subtree of nodePtr
  BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType ** successor);

  // search for target node
  bool findNode(BinaryNode<ItemType>* treePtr, ItemType * target, vector<ItemType*>* vec);

  // print Items indented
  void _printIndented(void visit(ItemType *), BinaryNode<ItemType>* nodePtr, int level);

  // printing Tree Breadth-First Traversal by level
  void _breadthFisrtTraversal(void visit(ItemType *), BinaryNode<ItemType>* nodePtr);

public:
  // Constructor
  BinarySearchTree(int comparator(ItemType *, ItemType *)) {
    this->comparator = comparator;
  }
  // insert a node at the correct location
  bool insert(ItemType * newEntry);
  // remove a node if found
  bool remove(ItemType * anEntry);
  // find a target node
  bool getEntry(ItemType * target, vector<ItemType*>* vec);
  // print item in indented manner
  void printIndented(void visit(ItemType *)) { _printIndented(visit, rootPtr, 1); }
  // print breadth first traversal
  void breadthFisrtTraversal(void visit(ItemType *)) { _breadthFisrtTraversal(visit, rootPtr); }
  // find and print longest branch in the tree
};

///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(ItemType* newEntry)
{
  BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
  rootPtr = _insert(rootPtr, newNodePtr);
  return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(ItemType* target)
{
  bool isSuccessful = false;
  rootPtr = _remove(rootPtr, target, isSuccessful);
  return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType* anEntry, vector<ItemType*>* vec)
{
  if (findNode(rootPtr, anEntry, vec)) {
    return true;
  }
  return false;
}

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
  BinaryNode<ItemType>* newNodePtr)
{
  if (nodePtr == NULL) {
    return newNodePtr;
  }
  else if (comparator(newNodePtr->getItem(), nodePtr->getItem()) == -1) {
    BinaryNode<ItemType> *leftNodePtr = _insert(nodePtr->getLeftPtr(), newNodePtr);
    nodePtr->setLeftPtr(leftNodePtr);
    return nodePtr;
  }
  else {
    BinaryNode<ItemType> *rightNodePtr = _insert(nodePtr->getRightPtr(), newNodePtr);
    nodePtr->setRightPtr(rightNodePtr);
    return nodePtr;
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
   ItemType* target, bool& success)
{
  if (nodePtr == 0)
  {
    success = false;
    return NULL;
  }
  if ((comparator(nodePtr->getItem() , target)) == 1) {
    BinaryNode<ItemType> *leftNodePtr = _remove(nodePtr->getLeftPtr(), target, success);
    nodePtr->setLeftPtr(leftNodePtr);
    return nodePtr;
  }
  else if (comparator(nodePtr->getItem() , target) == -1) {
    BinaryNode<ItemType> *rightNodePtr = _remove(nodePtr->getRightPtr(), target, success);
    nodePtr->setRightPtr(rightNodePtr);
    return nodePtr;
  }
  else
  {
    *target = *nodePtr->getItem();
    nodePtr = deleteNode(nodePtr);
    success = true;
    return nodePtr;
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
  if (nodePtr->isLeaf())
  {
    delete nodePtr;
    nodePtr = NULL;
    return nodePtr;
  }
  else if (nodePtr->getLeftPtr() == NULL)
  {
    BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
    delete nodePtr;
    nodePtr = NULL;
    return nodeToConnectPtr;
  }
  else if (nodePtr->getRightPtr() == NULL)
  {
    BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
    delete nodePtr;
    nodePtr = NULL;
    return nodeToConnectPtr;
  }
  else
  {
    ItemType* newNodeValue = NULL;
    // Return value of removeLeftmostNode() is the new right child.
    // newNodeValue is the leftmost child of right subtree.
    nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), &newNodeValue));
    nodePtr->setItem(newNodeValue);
    return nodePtr;
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
  ItemType** successor)
{
  if (nodePtr->getLeftPtr() == 0)
  {
    *successor = nodePtr->getItem();
    return deleteNode(nodePtr);
  }
  else
  {
    nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
    return nodePtr;
  }
}


template<class ItemType>
bool BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
  ItemType * target, vector<ItemType*>* vec) {
  if (nodePtr == NULL) {
    return false;
  }

  if (comparator(nodePtr->getItem(), target) == 0) {
    *target = *(nodePtr->getItem());
    vec->push_back(nodePtr->getItem());
  }
  
  if (comparator(nodePtr->getItem(), target) == 1) {
    findNode(nodePtr->getLeftPtr(), target, vec);
  }
  else {
    findNode(nodePtr->getRightPtr(), target, vec);
  }
  return !vec->empty();
}

template<class ItemType>
void BinarySearchTree<ItemType>::_printIndented(void visit(ItemType*),
  BinaryNode<ItemType>* nodePtr, int level) {
  if (nodePtr == NULL) {
    return;
  }
  for (int i = 1; i < level; ++i) {
    cout << "   ";
  }
  cout << level;
  ItemType* item = nodePtr->getItem();
  visit(item);
  _printIndented(visit, nodePtr->getRightPtr(), level + 1);
  _printIndented(visit, nodePtr->getLeftPtr(), level + 1);
}

template<class ItemType>
void BinarySearchTree<ItemType>::_breadthFisrtTraversal(void visit(ItemType*),
  BinaryNode<ItemType>* nodePtr) {
  Queue<BinaryNode<ItemType>*> queue;
  if (nodePtr) {
    queue.enqueue(nodePtr);
  }

  while (!queue.isEmpty()) {
    BinaryNode<ItemType>* temp_node;
    queue.dequeue(temp_node);
    ItemType* item = temp_node->getItem();
    visit(item);

    if (temp_node->getLeftPtr()) {
      queue.enqueue(temp_node->getLeftPtr());
    }
    if (temp_node->getRightPtr()) {
      queue.enqueue(temp_node->getRightPtr());
    }
  }
}
#endif