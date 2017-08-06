/*
Pointers, Stacks & Queues

There are a number of errors (about 10) in the following program.
Locate all errors, fix them (as shown below), run the program and save its output.

Here is an example:

int num = 10;
int *ptr;

num = &ptr; // <== Error: Comment the line and write the correct line below

// num = &ptr; // Error #1
ptr = &num;

NAME: Rashmi Baheti
IDE: Visual Studio
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define NUM_STU 6

typedef struct
{
  char  name[31];
  int   midterm[2];
  int   final;
} STUDENT;

typedef struct node NODE;
struct node
{
  STUDENT     data;
  //struct node next;   // Error #1
  struct node* next;
};

void printStu(const STUDENT *pStu);
NODE *push(NODE *stack, const STUDENT *pStu);
NODE *pop(NODE **stack);
void enqueue(NODE **queue, NODE **rear, const STUDENT *pStu);
NODE *dequeue(NODE **queue, NODE **rear);

int main(void)
{
  STUDENT stuList[NUM_STU] =
  {
    { "Taylor, Noah",{ 85, 94 }, 92 },
    { "Smith, Olivia",{ 91, 89 }, 86 },
    { "Brown, Liam",{ 87, 88 }, 90 },
    { "Davis, Emma",{ 96, 88 }, 97 },
    { "Garcia, Mason",{ 79, 93 }, 92 },
    { "Lopez, Sophia",{ 83, 78 }, 95 }
  };

  //NODE *stack; // Error #4
  NODE *stack = NULL;
  NODE *top = NULL;
  NODE *queue = NULL, *rear = NULL;
  //NODE front; // Error #2
  NODE *front = NULL;
  int i, n, count = 4;

  // build stack and queue with data from an array of STUDENT structures
  srand((unsigned int)time(NULL));
  for (n = 0; n < count; n++)
  {
    i = rand() % NUM_STU;
    // push(stack, &stuList[i]); // Error #9
    push(&stack, &stuList[i]);
    //enqueue(&queue, &rear, stuList[i]); // Error #3
    enqueue(&queue, &rear, &stuList[i]);
  }

  // display stack
  printf("STACK contents from top to bottom:\n");
  // while ((top = pop(stack))) //  Error #5
  while ((top = pop(&stack))) // top != NULL
  {
    printStu(&top->data);
    // Error #7  (Need to free every node in the stack)
    free(top); 
  }
  printf("\n\n");

  // display queue
  printf("QUEUE contents from front to rear:\n");
  // while ((front = dequeue(queue, rear))) // Error #6
  while ((front = dequeue(&queue, &rear))) // front != NULL
  {
    printStu(&front->data);
    // Error #8 (Need to free every node in the queue)
    free(front); 
  }
  printf("\n\n");

#ifdef _MSC_VER
  printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

  return 0;
}
/***************************************************
Displays the fileds of a STUDENT structure
Pre   pStu - a pointer to a STUDENT structure
Post
*/
void printStu(const STUDENT *pStu)
{
  printf("%-30s %4d %4d %4d\n",
    pStu->name,
    pStu->midterm[0],
    pStu->midterm[1],
    pStu->final);
}
/***************************************************
Stack Insert: insert in the beginning
*/
// NODE *push(NODE *stack, const STUDENT *pStu) // Error #10
NODE *push(NODE **stack, const STUDENT *pStu)
{
  NODE *pnew;

  pnew = (NODE *)malloc(sizeof(NODE));
  if (!pnew)
  {
    printf("... error in push!\n");
    exit(1);
  }
  pnew->data = *pStu;
  pnew->next = *stack;
  *stack = pnew;

  return *stack;
}

/***************************************************
Stack Delete: delete the first node
*/
NODE *pop(NODE **stack)
{
  NODE *first;

  if (*stack == NULL) return NULL;
  first = *stack;
  *stack = (*stack)->next;
  first->next = NULL;

  return first;
}

/***************************************************
Queue Insert: insert at the end
*/
void enqueue(NODE **queue, NODE **rear, const STUDENT *pStu)
{
  NODE *pnew;

  pnew = (NODE *)malloc(sizeof(NODE));
  if (!pnew)
  {
    printf("... error in enqueue!\n");
    exit(1);
  }
  pnew->data = *pStu;
  pnew->next = NULL;
  if (*queue == NULL) *queue = pnew;
  else (*rear)->next = pnew;
  *rear = pnew;
  return;
}

/***************************************************
Queue Delete: remove the first node
*/
NODE *dequeue(NODE **queue, NODE **rear)
{
  NODE *first;

  if (*queue == NULL) return NULL;
  first = *queue;
  *queue = (*queue)->next;
  if (*queue == NULL) *rear = NULL;
  first->next = NULL;

  return first;
}

/*	================= Sample Output ================= */
/*	Results:
STACK contents from top to bottom:
Garcia, Mason                    79   93   92
Lopez, Sophia                    83   78   95
Garcia, Mason                    79   93   92
Brown, Liam                      87   88   90


QUEUE contents from front to rear:
Brown, Liam                      87   88   90
Garcia, Mason                    79   93   92
Lopez, Sophia                    83   78   95
Garcia, Mason                    79   93   92


No Memory Leak


*/
