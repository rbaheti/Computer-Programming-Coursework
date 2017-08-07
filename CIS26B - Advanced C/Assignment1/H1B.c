#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

typedef struct
{
  char productName[26];
  int quantity;
} HARDWARE;

// Function prototypes.
void insertionSort(HARDWARE list[], int arrSize);
void printInventory(HARDWARE list[], int arrSize);
void readInputFile(HARDWARE **list, int *arrSize);

int main(void)
{
  HARDWARE *pHwareList = NULL;
  int arrSize = 0;
  readInputFile(&pHwareList, &arrSize);
  printf("\nFile was successfully read.\n\n");

  insertionSort(pHwareList, arrSize);

  printInventory(pHwareList, arrSize);

  // Free dynamically allocated memory.
  free(pHwareList);

  // Check for memory leak.
#ifdef _MSC_VER
  printf(_CrtDumpMemoryLeaks() ? "\nMemory Leak\n" : "\nNo Memory Leak\n");
#endif

  getchar();
  return 0;
}

/*	========================================================
Read the input file and populate the array of structure HARDWARE.
Pre   list and array size must be non NULL.
Post  Array of structure HARDWARE has been populated.
*/
void readInputFile(HARDWARE **list, int *arrSize) {
  HARDWARE *pHwareList;
  char ch, file_name[25];
  printf("Enter the name of the input file to read: ");
  gets(file_name);

  FILE *fpData;
  if ((fpData = fopen(file_name, "r")) == NULL) {
    printf("There was an error while opening your file.\n");
    printf("Hence, we will use in.txt file to read.\n");
    if ((fpData = fopen("in.txt", "r")) == NULL)
    {
      printf("Error opening in.txt for reading\n");
      getchar();
      exit(101);
    }
  }

  fscanf(fpData, "%d", arrSize);
  // Dynamically allocate array of HARDWARE structure.
  pHwareList = (HARDWARE*)calloc(*arrSize, sizeof(HARDWARE));

  int i = 0;
  while ((ch = fgetc(fpData)) != EOF)
  {
    ungetc(ch, fpData);
    fscanf(fpData, "%[^:]: %d", (pHwareList + i)->productName, &(pHwareList + i)->quantity);
    ++i;
  }

  // Close the input file.
  if (fclose(fpData) == EOF)
  {
    printf("Error closing in.txt!");
    exit(201);
  }
  *list = pHwareList;
}

/*	========================================================
Sort list using Insertion Sort.
Pre   list[] must contain at least one element
size is the size of list.
Post  list has been rearranged in ascending order.
*/
void insertionSort(HARDWARE list[], int arrSize)
{
  HARDWARE  temp;
  HARDWARE *pCurr;
  HARDWARE *pWalk;

  for (pCurr = list + 1; pCurr <= list + arrSize - 1; pCurr++)
  {
    temp = *pCurr;
    pWalk = pCurr - 1;
    while (pWalk >= list && strcmp(temp.productName, pWalk->productName) < 0)
    {
      *(pWalk + 1) = *pWalk;
      pWalk--;
    }
    *(pWalk + 1) = temp;
  }
}

/*	========================================================
Find out the total product quantity per product and
print it on the screen and to a file.
Pre   list[] must contain at least one element
size is the size of list.
Post  Inventory has been printed to the output file
and on the screen.
*/
void printInventory(HARDWARE pHwareList[], int arrSize)
{
  char filename[25] = "out.txt";
  char ch[50];
  printf("Do you want to provide the name of the output file name?\n");
  printf("Enter 'Y' for yes or 'N' for no:");
  gets(ch);
  if (toupper(ch[0]) == 'Y' && ch[1] == '\0') {
    printf("Please enter your output file name: ");
    gets(filename);
  }
  else {
    printf("Output will be written to out.txt\n");
  }
  FILE *fpData = fopen(filename, "w");
  if (fpData == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }

  int currentQty = 0, totalQty = 0;
  fprintf(fpData, "          ");
  for (int i = 0; i <= arrSize - 1; ++i)
  {
    if (strcmp(pHwareList[i].productName, pHwareList[i + 1].productName) == 0)
    {
      currentQty += pHwareList[i].quantity;
    }
    else
    {
      printf("%s %d", pHwareList[i].productName, currentQty + pHwareList[i].quantity);
      fprintf(fpData, "%s: %d", pHwareList[i].productName, currentQty + pHwareList[i].quantity);
      currentQty = 0;
      ++totalQty;
    }
  }
  printf("\n");
  rewind(fpData);
  fprintf(fpData, "%d", totalQty);
  if (fclose(fpData) == EOF)
  {
    printf("Error closing file!");
    exit(201);
  }
}


/*	================= Sample Output ================= */
/*
Enter the name of the input file to read: abc.txt
There was an error while opening your file.
Hence, we will use in.txt file to read.

File was successfully read.

Do you want to provide the name of the output file name?
Enter 'Y' for yes or 'N' for no:n
Output will be written to out.txt

ACETYLENE TORCH 10
BOLT (REGULAR) 1311
BRACE 234
CEMENT BAGS 113
CLAMP 523
FLASH LIGHT 535
HAMMER 60
LEVEL 122
MOLLY BOLT 80
NAIL 3579
PLANE 67
RIVET 89
SANDER 117
SAW 336
SAW BLADE 675
SCREW DRIVER 988
SLEDGE HAMMER 27
SOCKET SET 147
THERMOSTAT 141
VISE 44
WALL MOUNT 90
WELDING TORCH 107
WIDGET 32
WING NUT 89
WRENCH 452

No Memory Leak

*/