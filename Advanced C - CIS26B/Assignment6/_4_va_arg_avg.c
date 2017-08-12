/*********************************************************
CIS 26B -  Advanced C Programming
Write a function named findAvg that finds the average of
of the integer arguments. It also displays the parameters
greater than or equal to the average.

Eztra Credit:
/*********************************************************/

#include <stdio.h>
#include <stdarg.h>

// function prototype
double findAvg(int n, ...);

int main(void)
{
  printf("The average is: %.1f\n\n", findAvg(3, 20, 90, 10));
  printf("The average is: %.1f\n\n", findAvg(4, 20, 10, 50, 31));
  printf("The average is: %.1f\n\n", findAvg(2, 22, 13));
  printf("The average is: %.1f\n\n", findAvg(1, 13));
  printf("The average is: %.1f\n\n", findAvg(5, -20, 11, -53, -30, -90));

  getchar();
  return 0;
}

/**
Finds the average of any number of integer arguments.
Then displays the parameters greater than or equal to the average.
*/
double findAvg(int n, ...)
{
  va_list argp;
  va_start(argp, n);

  int sum = 0;
  int total_integers = n;

  while (total_integers--)
  {
    sum += va_arg(argp, int);
    // get the current argument
    // move argp to the next unnamed argument
  }
  //find average
  double avg = (double)sum / n;

  // print the parameters greater than or equal to the average.
  total_integers = n;
  va_start(argp, n);
  printf("Values larger or equal to the average value are: ");
  while (total_integers--)
  {
    int find_large = va_arg(argp, int);
    if (find_large >= avg)
      printf("%d ", find_large);
  }
  printf("\n");

  va_end(argp);
  return avg;
}