// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Rashmi Baheti.

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include <algorithm>
#include "BinaryTree.h"
#include "Queue.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
  // internal insert node: insert newNode in nodePtr subtree
  BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
  void _insert2(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr);

  // internal remove node: locate and delete target node under nodePtr subtree
  BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

  // delete target node from tree, called by internal remove node
  BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

  // remove the leftmost node in the left subtree of nodePtr
  BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

  // search for target node
  BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, ItemType & target) const;

  // print Items indented
  void _printIndented(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level);

  // printing Tree Breadth-First Traversal by level
  void _breadthFisrtTraversal(void visit(ItemType &), BinaryNode<ItemType>* nodePtr);

  // find longest branch
  void _longestBranch(BinaryNode<ItemType>* nodePtr, Queue<BinaryNode<ItemType>*>& queue);

  // iterative depth-first traversal
  void _IterativeInOrderTraversal(BinaryNode<ItemType>* rootPtr, void visit(ItemType &));

  // iterative depth-first traversal
  void _IterativePreOrderTraversal(BinaryNode<ItemType>* rootPtr, void visit(ItemType &));

  // iterative depth-first traversal
  void _IterativePostOrderTraversal(BinaryNode<ItemType>* nodePtr, void visit(ItemType &));

public:
  // insert a node at the correct location
  bool insert(const ItemType & newEntry);
  // remove a node if found
  bool remove(const ItemType & anEntry);
  // find a target node
  bool getEntry(ItemType & target) const;
  // print item in indented manner
  void printIndented(void visit(ItemType &)) { _printIndented(visit, rootPtr, 1); }
  // print breadth first traversal
  void breadthFisrtTraversal(void visit(ItemType &)) { _breadthFisrtTraversal(visit, rootPtr); }
  // find and print longest branch in the tree
  void longestBranch(void visit(ItemType &)); 
  // print in-order depth-first traversal using iterative method
  void IterativeInOrderTraversal(void visit(ItemType &));
  // print pre-order depth-first traversal using iterative method
  void IterativePreOrderTraversal(void visit(ItemType &));
  // print post-order depth-first traversal using iterative method
  void IterativePostOrderTraversal(void visit(ItemType &));
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
  BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
  rootPtr = _insert(rootPtr, newNodePtr);
  return true;
  /*BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
  if (!rootPtr) {
    rootPtr = newNodePtr;
  }
  else {
    _insert2(rootPtr, newNodePtr);
  }
  return true;*/
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
  bool isSuccessful = false;
  rootPtr = _remove(rootPtr, target, isSuccessful);
  return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(ItemType& anEntry) const
{
  if (findNode(rootPtr, anEntry)) {
    return true;
  }
  return false;
}

template<class ItemType>
void BinarySearchTree<ItemType>::longestBranch(void visit(ItemType &)){
  Queue<BinaryNode<ItemType>*> queue;
  _longestBranch(rootPtr, queue);

  Stack<BinaryNode<ItemType>*> stack;
  while (!queue.isEmpty()) {
    BinaryNode<ItemType>* nodePtr;
    queue.dequeue(nodePtr);
    stack.push(nodePtr);
  }
  cout << "Longest Branch: " << endl;
  while (!stack.isEmpty()) {
    BinaryNode<ItemType>* nodePtr;
    stack.pop(nodePtr);
    ItemType item = nodePtr->getItem();
    visit(item);
  }
}

template<class ItemType>
void BinarySearchTree<ItemType>::IterativeInOrderTraversal(void visit(ItemType &)) {
  _IterativeInOrderTraversal(rootPtr, visit);
}

template<class ItemType>
void BinarySearchTree<ItemType>::IterativePreOrderTraversal(void visit(ItemType &)) {
  _IterativePreOrderTraversal(rootPtr, visit);
}

template<class ItemType>
void BinarySearchTree<ItemType>::IterativePostOrderTraversal(void visit(ItemType &)) {
  _IterativePostOrderTraversal(rootPtr, visit);
}

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
  BinaryNode<ItemType>* newNodePtr)
{
  if (nodePtr == NULL) {
    return newNodePtr;
  }
  else if (newNodePtr->getItem() < nodePtr->getItem()) {
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
void BinarySearchTree<ItemType>::_insert2(BinaryNode<ItemType>* nodePtr,
  BinaryNode<ItemType>* newNodePtr)
{
  if (newNodePtr->getItem() < nodePtr->getItem()) {
    if (nodePtr->getLeftPtr()) {
      _insert(nodePtr->getLeftPtr(), newNodePtr);
    }
    else {
      nodePtr->setLeftPtr(newNodePtr);
    }
  }
  else {
    if (nodePtr->getRightPtr()) {
      _insert(nodePtr->getRightPtr(), newNodePtr);
    }
    else {
      nodePtr->setRightPtr(newNodePtr);
    }
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
  const ItemType target, bool& success)
{
  if (nodePtr == 0)
  {
    success = false;
    return NULL;
  }
  if (nodePtr->getItem() > target) {
    BinaryNode<ItemType> *leftNodePtr = _remove(nodePtr->getLeftPtr(), target, success);
    nodePtr->setLeftPtr(leftNodePtr);
    return nodePtr;
  }
  else if (nodePtr->getItem() < target) {
    BinaryNode<ItemType> *rightNodePtr = _remove(nodePtr->getRightPtr(), target, success);
    nodePtr->setRightPtr(rightNodePtr);
    return nodePtr;
  }
  else
  {
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
    ItemType newNodeValue;
    nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
    nodePtr->setItem(newNodeValue);
    return nodePtr;
  }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
  ItemType & successor)
{
  if (nodePtr->getLeftPtr() == 0)
  {
    successor = nodePtr->getItem();
    return deleteNode(nodePtr);
  }
  else
  {
    nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
    return nodePtr;
  }
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
  ItemType & target) const {
  if (nodePtr == NULL) {
    return NULL;
  }

  if (nodePtr->getItem() == target) {
    target = nodePtr->getItem();
    return nodePtr;
  }
  else if (nodePtr->getItem() > target) {
    return findNode(nodePtr->getLeftPtr(), target);
  }
  else {
    return findNode(nodePtr->getRightPtr(), target);
  }
}

template<class ItemType>
void BinarySearchTree<ItemType>::_printIndented(void visit(ItemType&), 
  BinaryNode<ItemType>* nodePtr, int level) {
  if (nodePtr == NULL) {
    return;
  } 
  for (int i = 1; i < level; ++i) {
    cout << "\t";
  }
  cout << level;
  ItemType item = nodePtr->getItem();
  visit(item);
  _printIndented(visit, nodePtr->getRightPtr(), level+1);
  _printIndented(visit, nodePtr->getLeftPtr(), level+1);
}

template<class ItemType>
void BinarySearchTree<ItemType>::_breadthFisrtTraversal(void visit(ItemType&),
  BinaryNode<ItemType>* nodePtr) {
  Queue<BinaryNode<ItemType>*> queue;
  if (nodePtr) {
    queue.enqueue(nodePtr);
  }

  while (!queue.isEmpty()) {
    BinaryNode<ItemType>* temp_node;
    queue.dequeue(temp_node);
    ItemType item = temp_node->getItem();
    visit(item);

    if (temp_node->getLeftPtr()) {
      queue.enqueue(temp_node->getLeftPtr());
    }
    if (temp_node->getRightPtr()) {
      queue.enqueue(temp_node->getRightPtr());
    }
  }
}

template<class ItemType>
void BinarySearchTree<ItemType>::_longestBranch(BinaryNode<ItemType>* nodePtr, Queue<BinaryNode<ItemType>*>& queue) {
  Queue<BinaryNode<ItemType>*> left_queue, right_queue;
  if (nodePtr->getLeftPtr()) {
    _longestBranch(nodePtr->getLeftPtr(), left_queue);
  }
  if (nodePtr->getRightPtr()) {
    _longestBranch(nodePtr->getRightPtr(), right_queue);
  }

  if (left_queue.getCount() > right_queue.getCount()) {
    while (!left_queue.isEmpty()) {
      BinaryNode<ItemType>* tempNode;
      left_queue.dequeue(tempNode);
      queue.enqueue(tempNode);
    }
  }
  else {
    while (!right_queue.isEmpty()) {
      BinaryNode<ItemType>* tempNode;
      right_queue.dequeue(tempNode);
      queue.enqueue(tempNode);
    }
  }
  queue.enqueue(nodePtr);
}

/*
template<class ItemType>
int BinarySearchTree<ItemType>::_longestBranch( BinaryNode<ItemType>* nodePtr) {
if (nodePtr == NULL) {
return 0;
}
int left = _longestBranch(visit, nodePtr->getLeftPtr());
int right = _longestBranch(visit, nodePtr->getRightPtr());
return max(left, right) + 1;
}*/

template<class ItemType>
void BinarySearchTree<ItemType>::_IterativeInOrderTraversal(BinaryNode<ItemType>* rootPtr, void visit(ItemType&)) {
  if (rootPtr == NULL) {
    return;
  }

  // This stack stores nodes whose both children need to be visited.
  Stack<BinaryNode<ItemType>*> stack;
  // This stack stores nodes whose only right child needs to be visited.
  Stack<BinaryNode<ItemType>*> left_visited_stack;
  
  stack.push(rootPtr);
  while (true) {
    if (!stack.isEmpty()) {
      BinaryNode<ItemType>* nodePtr; 
      stack.pop(nodePtr);
    
      if (nodePtr->getLeftPtr()) {
        // Add left child to stack and nodePtr to left_visited_stack.
        stack.push(nodePtr->getLeftPtr());
      }
      left_visited_stack.push(nodePtr);
    }
    else if (!left_visited_stack.isEmpty()) {
      BinaryNode<ItemType>* nodePtr;
      left_visited_stack.pop(nodePtr);
      
      ItemType item = nodePtr->getItem();
      visit(item);

      if (nodePtr->getRightPtr()) {
        // Add right child to stack.
        stack.push(nodePtr->getRightPtr());
      }
    }
    else {
      break;
    }
  }
}

template<class ItemType>
void BinarySearchTree<ItemType>::_IterativePreOrderTraversal(BinaryNode<ItemType>* rootPtr, 
  void visit(ItemType&)) {
  if (rootPtr == NULL) {
    return;
  }
  Stack<BinaryNode<ItemType>*> stack;
  stack.push(rootPtr);
  while (!stack.isEmpty()) {
    BinaryNode<ItemType>* nodePtr;
    stack.pop(nodePtr);
    ItemType item = nodePtr->getItem();
    visit(item);
    if (nodePtr->getRightPtr()) {
      stack.push(nodePtr->getRightPtr());
    }
    if (nodePtr->getLeftPtr()) {
      stack.push(nodePtr->getLeftPtr());
    }
  }
}

template<class ItemType>
void BinarySearchTree<ItemType>::_IterativePostOrderTraversal(BinaryNode<ItemType>* rootPtr,
  void visit(ItemType&)) {
  if (rootPtr == NULL) {
    return;
  }
  
  // This stack stores nodes whose both children need to be visited.
  Stack<BinaryNode<ItemType>*> stack;
  // This stack stores nodes whose children have already been visited.
  Stack<BinaryNode<ItemType>*> children_visited_stack; 
  stack.push(rootPtr);
  while (true) {
    if (!stack.isEmpty()) {
      BinaryNode<ItemType>* nodePtr;
      stack.pop(nodePtr);

      if (nodePtr->getLeftPtr()) {
        // Add left child to stack.
        stack.push(nodePtr->getLeftPtr());
      }
      
      if (nodePtr->getRightPtr()) {
        // Add right child to stack.
        stack.push(nodePtr->getRightPtr());
      }
            
      children_visited_stack.push(nodePtr);
    }
    else if (!children_visited_stack.isEmpty()) {
      BinaryNode<ItemType>* nodePtr;
      children_visited_stack.pop(nodePtr);

      ItemType item = nodePtr->getItem();
      visit(item);
    }
    else {
      break;
    }
  }
}
#endif