#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct node QUEUENODE;
struct node
{
  int lineNum;
  struct node *next;
};

typedef struct nodeTag {
  char key[100];
  struct nodeTag *left;
  struct nodeTag *right;
  QUEUENODE *line_num_queue_head;
  QUEUENODE *line_num_queue_rear;
} NODE;

// Function prototypes.
void printTreeInorder(NODE *root);
void printNode(NODE *root, char* data);
int insert(NODE **root, char data[50], int line_num);
void destroyBST(NODE *root);
void enqueue(QUEUENODE **queue, QUEUENODE **rear, int data);
void printQueue(QUEUENODE *queue);
int peekRearValue(QUEUENODE *rear);
void destroyQueue(QUEUENODE *queue);
void readInputFile(char* inputFilename, NODE *root);
void printInputFile(char* inputFilename);
void searchIdentifier(NODE *root);
void printTimeStamp();