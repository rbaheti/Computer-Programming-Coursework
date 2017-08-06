/**
 Project: BUILD A BINARY SEARCH TREE - ADT

 - use void *
 - use function pointers
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BST.h"

using namespace std;

void build_BST( BST &tree, int n );
int  compareInt (void* num1, void* num2);
void printData   (void* data);

int main( void )
{
   BST tree(compareInt);
   int n = 5; // number of nodes

   srand(time(0));
   build_BST(tree, n );
   tree.BST_InorderTraverse(printData);

   return 0;
}

/**~*~*
   Builds a random Binary Search Tree of integer numbers within the range
   [0, 99]
*/
void build_BST( BST &tree, int n )
{
    int *data;

    while(n--)
    {
        data = new int;
        *data = rand() % 100;
        tree.BST_insert((void *)data);
    }
}

/**~*~*
   	Compare two integers:  num1 and num2 are valid pointers to integers
    Return low (-1), equal (0), or high (+1)
*~**/
int compareInt (void* num1, void* num2)
{
    int key1 = *((int*)num1); /// you cannot dereference a void pointer:
	int key2 = *((int*)num2); /// cast it first, then dereference it!

	if (key1 < key2)
	    return -1;
	if (key1 == key2)
	    return 0;
	return 1;
}

/**~*~*
   	Print one integer from BST: data is a pointer to an integer
*~**/
void printData (void* data)
{
	cout << *((int*)data) << endl;
	return;
}
