/*********************************************************
CIS 26B -  Advanced C Programming
Write a function named findMax that finds the maximum of
any number of integer arguments.

Extra Credit:
/*********************************************************/

#include <stdio.h>
#include <stdarg.h>

// function prototype
int findMax(int n, ...);

int main(void)
{
  printf("The largest is: %d\n", findMax(3, 20, 90, 10));
  printf("The largest is: %d\n", findMax(4, 20, 10, 50, 30));
  printf("The largest is: %d\n", findMax(2, 20, 10));
  printf("The largest is: %d\n", findMax(1, 13));
  printf("The largest is: %d\n", findMax(5, -20, 10, -50, -30, -90));

  getchar();
  return 0;
}

/**
Finds the maximum of any number of integer arguments.
*/
int findMax(int n, ...)
{
  va_list argp;
  va_start(argp, n);

  int max = va_arg(argp, int);

  while (n--)
  {
    int temp = va_arg(argp, int);
    if (max < temp)
      max = temp;
    // get the current argument
    // move argp to the next unnamed argument
  }

  va_end(argp); 
  return max;
}