/*********************************************************
CIS 26B -  Advanced C Programming
Write a function named display that takes any number of arguments.
The first argument must be an integer.
The remaining arguments will be strings.
The first argument specifies the number of strings.

Extra Credit:
/*********************************************************/

#include <stdio.h>
#include <stdarg.h>

// function prototype
void display(int n, ...);

int main(void)
{
  display(5, "one", "two", "three", "four", "five");
  display(2, "dog", "cat");
  display(4, "dog", "cat", "mouse", "bird");
  display(3, "cat", "mouse", "bird");

  getchar();
  return 0;
}

/**
Displays any number of char* arguments.
*/
void display(int n, ...)
{
  va_list argp;
  va_start(argp, n);

  while (n--)
  {
    char* string = va_arg(argp, char*);
    // get the current argument
    // move argp to the next unnamed argument

    printf("%s ", string);
  }
  printf("\n");

  va_end(argp);
  return;
}
