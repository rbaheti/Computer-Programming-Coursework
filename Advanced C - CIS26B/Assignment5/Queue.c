#define  _CRT_SECURE_NO_WARNINGS
#include "HW5.h"

/*****************************************************************
Queue Insert: insert at the end
*/
void enqueue(QUEUENODE **queue, QUEUENODE **rear, int data)
{
  QUEUENODE *pnew = (QUEUENODE *)malloc(sizeof(QUEUENODE));
  if (!pnew)
  {
    printf("... error in enqueue!\n");
    exit(1);
  }
  pnew->lineNum = data;
  pnew->next = NULL;

  if (*queue == NULL) {
    *queue = pnew;
    *rear = pnew;
  }
  else {
    (*rear)->next = pnew;
    *rear = pnew;
  }
  return;
}

/***************************************************
Queue peekRearValue: Returns the last value in the queue
*/

int peekRearValue(QUEUENODE *rear)
{
  if (!rear)
    return -1;

  return rear->lineNum;
}

/*	========================================================
Print the contents in the queue.
*/
void printQueue(QUEUENODE *queue) {
  while (queue) {
    printf("%3d ", queue->lineNum);
    queue = queue->next;
  }
  return;
}

/*	========================================================
Destroy Queue after its use.
*/
void destroyQueue(QUEUENODE *queue) {
  while (queue != NULL) {
    QUEUENODE *temp_queue = queue;
    queue = queue->next;
    free(temp_queue);
  }
}