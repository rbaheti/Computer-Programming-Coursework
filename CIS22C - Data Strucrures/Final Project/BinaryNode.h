#ifndef _BINARY_NODE_
#define _BINARY_NODE_

#include<string>
using namespace std;

template<class ItemType>
class BinaryNode
{
private:
  ItemType*             item;       // Data portion
  BinaryNode<ItemType>* leftPtr;		// Pointer to left child
  BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
  // constructors
  BinaryNode(ItemType* anItem) { item = anItem; leftPtr = NULL; rightPtr = NULL; }
  BinaryNode(ItemType* anItem,
    BinaryNode<ItemType>* left, 
    BinaryNode<ItemType>* right) {
    item = anItem; leftPtr = left; rightPtr = right;
  }
  // accessors
  void setItem(ItemType* anItem) { item = anItem; }
  void setLeftPtr(BinaryNode<ItemType>* left) { leftPtr = left; }
  void setRightPtr(BinaryNode<ItemType>* right) { rightPtr = right; }
  // mutators
  ItemType* getItem() const { return item; }
  BinaryNode<ItemType>* getLeftPtr() const { return leftPtr; }
  BinaryNode<ItemType>* getRightPtr() const { return rightPtr; }

  bool isLeaf() const { return (leftPtr == NULL && rightPtr == NULL); }
};
#endif 