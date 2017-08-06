// This program demonstrates the displayList member function.
#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
   // Define a pointer to a LinkedList object.
   LinkedList<double> *list;

   // Allocate
   list = new LinkedList<double>;

   // Append some values to the list.
   list->insertNode(5.1);
   list->insertNode(2.3);
   list->insertNode(9.7);
   list->insertNode(6.2);

   // Display the values in the list.
   list->displayList();

   delete list;
   return 0;
}
