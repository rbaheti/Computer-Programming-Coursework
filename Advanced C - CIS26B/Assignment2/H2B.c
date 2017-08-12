#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc(), free(), exit()
#include <assert.h> // assert()

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

#define DUMMY_TRAILER '\177'
// octal ASCII code of the
// last character in the ASCII table

typedef struct temperatureStack
{
  int temperature_value;
  struct temperatureStack *next;
} TEMPERATURE_STACK;

typedef  struct weatherData
{
  char state[50];
  char city[50];
  TEMPERATURE_STACK* temperature;
  struct weatherData* forw;
  struct weatherData* back;
} WEATHERDATA;

// Function prototypes.
void readInputFile(WEATHERDATA *list);
WEATHERDATA *init_list(void);
void insert(WEATHERDATA *list, WEATHERDATA *data);
TEMPERATURE_STACK *push(TEMPERATURE_STACK *stack, int data);
int peek(TEMPERATURE_STACK *stack);
void traverse_forw(WEATHERDATA *list);
void traverse_back(WEATHERDATA *list);
void search_data_in_list(WEATHERDATA *list);

int main(void)
{
  WEATHERDATA *pWData = init_list();
  readInputFile(pWData);

  printf("\nSorted list in ascending order is:\n");
  traverse_forw(pWData);

  printf("\nSorted list in descending order is:\n");
  traverse_back(pWData);

  search_data_in_list(pWData);

  // Free memory.
  pWData = pWData->forw; // skip the dummy node
  while (pWData->state[0] != DUMMY_TRAILER)
  {
    WEATHERDATA *temp_list = pWData;
    while (pWData->temperature != NULL) {
      TEMPERATURE_STACK *temp_stack = pWData->temperature;
      pWData->temperature = pWData->temperature->next;
      free(temp_stack);
    }
    pWData = pWData->forw;   
    free(temp_list);
  }
  free(pWData);
  
#ifdef _MSC_VER
  printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

  getchar();
  return 0;
}

/***************************************************
Read the input file and populate given linked list
with the records in the file.
Pre   list must be non NULL.
Post  list is populated with data read from the file.
*/
void readInputFile(WEATHERDATA *list) {
  char ch, file_name[25];
  printf("Enter the name of the input file to read: ");
  gets(file_name);

  FILE *fpData = NULL;
  if ((fpData = fopen(file_name, "r")) == NULL) {
    printf("There was an error while opening your file.\n");
    printf("Hence, we will use temperatures.txt file to read.\n");
    if ((fpData = fopen("temperatures.txt", "r")) == NULL)
    {
      printf("Error opening temperatures.txt for reading\n");
      getchar();
      exit(101);
    }
  }

  int i = 0;
  while ((ch = fgetc(fpData)) != EOF)
  {
    WEATHERDATA pWData;
    ungetc(ch, fpData);

    int temperature_value;
    fscanf(fpData, "%[^,],%[^:]:%d%*c", pWData.state, pWData.city, &temperature_value);

    pWData.temperature = NULL;  // push() requires that stack variable is NULL when it is empty.
    push(&pWData.temperature, temperature_value);

    insert(list, &pWData);

    free(pWData.temperature);  // free stack of pWData.
    ++i;
  }

  // Close the input file.
  if (fclose(fpData) == EOF)
  {
    printf("Error closing in.txt!");
    exit(201);
  }
}

/***************************************************
Initialization of a circularly doubly-linked
list with one sentinel node
Post  non-NULL pointer to the new linked list is returned.
*/
WEATHERDATA *init_list(void)
{
  WEATHERDATA *list;

  // allocate the sentinel node
  list = (WEATHERDATA *)malloc(sizeof(WEATHERDATA));
  if (!list)
  {
    printf("Error in init_list!\n");
    exit(1);
  }
  list->state[0] = DUMMY_TRAILER;
  list->state[1] = '\0';
  list->city[0] = DUMMY_TRAILER;
  list->city[1] = '\0';
  list->temperature = NULL;
  list->forw = list;
  list->back = list;

  return list;
}

/***************************************************
Insert a node in a sorted circularly
doubly-linked list with one sentinel node
Pre  list and data must be non-NULL.
Post  Given data is inserted into the linked list.
*/
void insert(WEATHERDATA *list, WEATHERDATA *data)
{
  WEATHERDATA *curr = list->forw;
  WEATHERDATA *prev = list;
  WEATHERDATA *pnew;

  // search
  while (strcmp(data->state, curr->state) > 0)
  {
    prev = curr;
    curr = curr->forw;
  }

  // if the state is same, then look for city.
  if (strcmp(data->state, curr->state) == 0) {
    while (strcmp(data->state, curr->state) == 0 && strcmp(data->city, curr->city) > 0)
    {
      prev = curr;
      curr = curr->forw;
    }
  }

  if (strcmp(data->state, curr->state) == 0 && strcmp(data->city, curr->city) == 0) {
    push(&curr->temperature, data->temperature->temperature_value);
  }

  if (strcmp(data->state, curr->state) && strcmp(data->city, curr->city))
  {
    // not a duplicate
    pnew = (WEATHERDATA *)malloc(sizeof(WEATHERDATA));
    if (!pnew)
    {
      printf("Fatal memory allocation error in insert!\n");
      exit(3);
    }
    strcpy(pnew->state, data->state);
    strcpy(pnew->city, data->city);
    pnew->temperature = NULL;  // push() requires that stack variable is NULL when it is empty.
    push(&pnew->temperature, data->temperature->temperature_value);
    pnew->forw = curr;
    pnew->back = prev;
    prev->forw = pnew;
    curr->back = pnew;
  } 
  return;
}

/***************************************************
Traverses forward a circularly doubly-linked
list with one sentinel node to print out the
contents of each node.
Pre  list must be non-NULL.
*/
void traverse_forw(WEATHERDATA *list)
{
  putchar('\n');
  list = list->forw; // skip the dummy node
  while (list->state[0] != DUMMY_TRAILER)
  {
    printf("%s, %s : %d\n", list->state, list->city, peek(list->temperature));
    list = list->forw;
  }
  return;
}

/***************************************************
Traverses backward a circularly doubly-linked
list with one sentinel node to print out the
contents of each node.
Pre  list must be non-NULL.
*/
void traverse_back(WEATHERDATA *list)
{
  putchar('\n');
  list = list->back; // skip the dummy node
  while (list->state[0] != DUMMY_TRAILER)
  {
    printf("%s, %s : %d\n", list->state, list->city, peek(list->temperature));
    list = list->back;
  }
  return;
}

/***************************************************
Stack Insert: insert node at the top of the stack.
*/
TEMPERATURE_STACK *push(TEMPERATURE_STACK **stack, int data)
{
  TEMPERATURE_STACK *pnew;

  pnew = (TEMPERATURE_STACK *)malloc(sizeof(TEMPERATURE_STACK));
  if (!pnew)
  {
    printf("... error in push!\n");
    exit(1);
  }
  pnew->temperature_value = data;
  pnew->next = *stack;
  *stack = pnew;
  return *stack;
}

/***************************************************
Returns the value at the top of the given stack.
*/
int peek(TEMPERATURE_STACK *stack)
{
  assert(stack != NULL);
  return stack->temperature_value;
}

/***************************************************
Prompts user to enter city and state name. Searches
the city and state in the linked list and prints
recent and average temperature data for the city.
*/
void search_data_in_list(WEATHERDATA *list)
{
  char user_input[100], city[50], state[50];
  printf("\nTo search state/city in the list, please enter the names in this format:\n");
  printf("State name,City name then press enter\n");

  while(1)
  {
    printf("\nEnter state/city name[or quit]: ");
    gets(user_input);
    if (strcmp(user_input, "quit") == 0)
      break;

    sscanf(user_input, "%[^,],%[^\n]\n", state, city);

    WEATHERDATA *test_node = NULL;
    // search for state/city in the list.
    list = list->forw; // skip the dummy node
    while (list->state[0] != DUMMY_TRAILER)
    {
      if (strcmp(list->state, state) == 0 && strcmp(list->city, city) == 0) {
        test_node = list;
        break;
      }
      list = list->forw;
    }
    if (test_node) {
      int temperature_sum = 0, count = 0;
      double temperature_avg = 0.0;
      TEMPERATURE_STACK* test_stack_node = test_node->temperature;

      while (test_stack_node != NULL) {
        temperature_sum += test_stack_node->temperature_value;
        count++;
        test_stack_node = test_stack_node->next;
      }
      temperature_avg = temperature_sum / (count*1.0);
      printf("Recent temperature of %s, %s is: %d\n", 
        test_node->state, test_node->city, peek(test_node->temperature));
      printf("Its average temperature is: %.1f degrees\n", temperature_avg);
    }
    else {
      printf("Entered state/city was not found in the list!\n");
    } 
  }
}

/******************  Sample Output  *******************

Enter the name of the input file to read: hds
There was an error while opening your file.
Hence, we will use temperatures.txt file to read.

Sorted list in ascending order is:

Arizona, Flagstaff : 84
Arizona, Tucson : 103
California, Los Angeles : 82
California, San Francisco : 68
California, Yreka : 100
Oregon, Salem : 85
Pennsylvania, Philadelphia : 86
Pennsylvania, Pittsburgh : 89

Sorted list in descending order is:

Pennsylvania, Pittsburgh : 89
Pennsylvania, Philadelphia : 86
Oregon, Salem : 85
California, Yreka : 100
California, San Francisco : 68
California, Los Angeles : 82
Arizona, Tucson : 103
Arizona, Flagstaff : 84

To search state/city in the list, please enter the names in this format:
State name,City name then press enter

Enter state/city name[or quit]: Arizona,Tucson
Recent temperature of Arizona, Tucson is: 103
Its average temperature is: 103.0 degrees

Enter state/city name[or quit]: xxx xx
Entered state/city was not found in the list!

Enter state/city name[or quit]: quit
No Memory Leak

*/