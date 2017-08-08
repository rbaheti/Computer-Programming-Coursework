#include "HW5.h"

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

int main(int argc, char* argv[])
{
  char inputFilename[100] = "input.c";
  if (argc > 1) {
    strcpy(inputFilename, argv[1]);
  }
  else {
    printf("Input filename is not specified through argv. Will use input.c instead.\n");
  }
  
  printf("/************************  Cross Reference Listing  ************************/\n\n");
  printTimeStamp();

  NODE *root = NULL;
  readInputFile(inputFilename, &root);
  printTreeInorder(root);
  printInputFile(inputFilename);
  searchIdentifier(root);

  destroyBST(root);
  root = NULL;

#ifdef _MSC_VER
  printf(_CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
#endif

  getchar();
  return 0;
}

/*	========================================================
Read given input file and populate given binary tree with 
nodes corresponding to identifiers found in the input file
*/
void readInputFile(char* inputFilename, NODE **root) {
  FILE *fpData;
  if ((fpData = fopen(inputFilename, "r")) == NULL) {
    printf("Error opening %s for reading.\n", inputFilename);
    getchar();
    exit(101);
  }

  char orig_line_string[300], line_string[300];
  int is_comment_ongoing = 0;
  int line_num = 0;
  while (fgets(orig_line_string, sizeof(orig_line_string), fpData) != NULL)
  {
    ++line_num;
    strcpy(line_string, orig_line_string);
    int linelength = strlen(orig_line_string);

    // Replace all words that are within double quotes with whitespace.
    char* quotebeginptr = strchr(line_string, '\"');
    if (quotebeginptr != NULL) {
      *quotebeginptr = ' ';
      while (*quotebeginptr != '\0') {
        if (*quotebeginptr == '\"') {
          *quotebeginptr = ' ';
          break;
        }
        else {
          *quotebeginptr = ' ';
        }
        ++quotebeginptr;
      }
    }

    // Replace all words that are within single quotes with whitespace.
    quotebeginptr = strchr(line_string, '\'');
    if (quotebeginptr != NULL) {
      *quotebeginptr = ' ';
      while (*quotebeginptr != '\0') {
        if (*quotebeginptr == '\'') {
          *quotebeginptr = ' ';
          break;
        }
        else {
          *quotebeginptr = ' ';
        }
        ++quotebeginptr;
      }
    }

    int skip_num_chars = 0;
    if (is_comment_ongoing && linelength >= 2) {
      char* commentend = strstr(orig_line_string, "*/");
      if (commentend == NULL) {
        continue;  // read next line from file
      }
      else {
        skip_num_chars = commentend + 2 - orig_line_string;
        is_comment_ongoing = 0;
      }
    }

    char *wordptr = strtok(line_string + skip_num_chars, " \t\n");
    while (wordptr != NULL)
    {
      int wordbeginindex = wordptr - line_string;
      char* strtokptr = wordptr + strlen(wordptr) + 1;
      if (strtokptr > line_string + linelength) {
        strtokptr = line_string + linelength;
      }

      // Ignore all words that are part of a single line comment.
      if (strlen(wordptr) >= 2 && wordptr[0] == '/' && wordptr[1] == '/') {
        break;
      }

      if (strlen(wordptr) >= 2 && wordptr[0] == '/' && wordptr[1] == '*') {
        is_comment_ongoing = 1;
        char* commentend = strstr(orig_line_string + wordbeginindex, "*/");
        if (commentend == NULL) {
          wordptr = NULL;
        }
        else {
          int commentendindex = commentend + 2 - orig_line_string;
          wordptr = strtok(line_string + commentendindex, " \t\n");
          is_comment_ongoing = 0;
        }
        continue;
      }

      char word[100];
      strcpy(word, wordptr);

      char *identifierptr = strtok(wordptr, "()*&%#!~+-=<>[].,:;{}|^");
      while (identifierptr != NULL)
      {
        char firstChar = *identifierptr;
        if (isalpha(firstChar) || firstChar == '_') {
          insert(root, identifierptr, line_num);
        }
        identifierptr = strtok(NULL, "()*&%#!~+-=<>[].,:;{}|^");
      }

      wordptr = strtok(strtokptr, " \t\n");
    }
  }

  // Close the input file.
  if (fclose(fpData) == EOF)
  {
    printf("Error closing %s!", inputFilename);
    exit(201);
  }
}

/*	========================================================
Print the input file on console with line numbers.
*/
void printInputFile(char* inputFilename) {
  FILE *fpData;
  if ((fpData = fopen(inputFilename, "r")) == NULL) {
    printf("Error opening %s for reading.\n", inputFilename);
    getchar();
    exit(101);
  }

  char orig_line_string[300];
  int line_num = 0;
  printf("\n");
  while (fgets(orig_line_string, sizeof(orig_line_string), fpData) != NULL)
  {
    ++line_num;
    printf("%3d: %s", line_num, orig_line_string);
  }
  printf("\n");

  // Close the input file.
  if (fclose(fpData) == EOF)
  {
    printf("Error closing %s!", inputFilename);
    exit(201);
  }
}

/*	========================================================
Ask user for an identifier and print details about the 
identifier using given binary tree.
*/
void searchIdentifier(NODE *root) {
  int keep_looping = 1;
  while (keep_looping != 0) {
    printf("\nEnter identifier to search or just press enter to exit: ");
    char inputStr[100] = { 0 }, identifier[100] = { 0 };
    gets(inputStr);

    int ignore_leading_spaces = strspn(inputStr, " \t");
    strcpy(inputStr, inputStr + ignore_leading_spaces);
    sscanf(inputStr, "%[^ ]", identifier);
    if (strlen(identifier) == 0) {
      keep_looping = 0;
    }
    else {
      int ignore_leading_spaces = strspn(inputStr + strlen(identifier), " \t");
      if (strcspn(inputStr + strlen(identifier) + ignore_leading_spaces, " \t") != 0) {
        printf("Please enter only one word.\n");
      }
      else {
        printNode(root, identifier);
      }
    }
  }
}

/*	========================================================
Print time stamp on console.
*/
void printTimeStamp() {
  struct tm *timeptr;
  time_t timeval;
  char buffer[80];
  time(&timeval);
  timeptr = localtime(&timeval);
  strftime(buffer, 80, "%c\n", timeptr);
  printf("Cross reference listing made at: %s\n\n", buffer);
}