#define  _CRT_SECURE_NO_WARNINGS
#include "HW5.h"

/****************************************************************
RECURSIVE Insert in binary search tree.
*/
int insert(NODE **root, char data[50], int line_num)
{
  if (!(*root)) { // parent found: insert data
                  // allocate the new node
    if (!(*root = (NODE *)malloc(sizeof(NODE))))
      printf("Fatal malloc error!\n"), exit(1);

    strcpy((*root)->key, data);

    // set left root and right root of new node to null.
    (*root)->left = (*root)->right = NULL;
    (*root)->line_num_queue_head = (*root)->line_num_queue_rear = NULL;
    enqueue(&(*root)->line_num_queue_head, &(*root)->line_num_queue_rear, line_num);
    return 1; // data inserted
  }

  if (strcmp(data, (*root)->key) > 0)
    return insert(&(*root)->right, data, line_num);
  else if (strcmp(data, (*root)->key) < 0)
    return insert(&(*root)->left, data, line_num);
  else
  {
    enqueue(&(*root)->line_num_queue_head, &(*root)->line_num_queue_rear, line_num);
    // printf("Node already in the tree!\n");
    return 0; // duplicate
  }
}


/****************************************************************
INORDER
Print a BST in Left-Root-Right sequence.
*/
void printTreeInorder(NODE *root)
{
  if (root == NULL) return;

  printTreeInorder(root->left);
  printf("%-30s ", root->key);
  printQueue(root->line_num_queue_head);
  printf("\n");
  printTreeInorder(root->right);
}

/****************************************************************
Print a node with given key.
*/
void printNode(NODE *root, char* data)
{
  if (root == NULL) {
    printf("Could not find any data corresponding to %s.\n", data);
    return;
  }

  if (strcmp(data, root->key) > 0)
    printNode(root->right, data);
  else if (strcmp(data, root->key) < 0)
    printNode(root->left, data);
  else
  {
    printf("%-30s ", root->key);
    printQueue(root->line_num_queue_head);
    printf("\n");
  }
}

/****************************************************************
Destroy binary search tree after its use.
*/
void destroyBST(NODE *root) {
  if (root == NULL) return;

  destroyBST(root->left);
  destroyBST(root->right);
  destroyQueue(root->line_num_queue_head);
  free(root);
}