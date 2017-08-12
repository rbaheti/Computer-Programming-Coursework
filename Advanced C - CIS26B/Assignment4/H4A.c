#include <stdio.h>

int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);
#define TURN_ON_MASK(numbits, startbit) ((~(((unsigned short)~0) << numbits)) << startbit);
#define TURN_OFF_MASK(numbits, startbit) ~((~(((unsigned short)~0) << numbits)) << startbit);

int main(void)
{
  unsigned short wrd = 65, a = 32, b, mask;
  int numbits = 3;
  int startbit = 2;

  printbits(wrd);

  //mask = (~(((unsigned short)~0) << numbits)) << startbit; // replace this by a macro with arguments
  b = a | TURN_ON_MASK(numbits, startbit);
  printf("Turn ON %d bits starting at bit#%d\n", numbits, startbit);
  printf("%d\n", a);
  printbits(a);
  printbits(b);
  printf("%d\n", b);

  a = 31;
  //mask = ~((~(((unsigned short)~0) << numbits)) << startbit); // replace this by a macro with arguments
  b = a & TURN_OFF_MASK(numbits, startbit);
  printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
  printf("%d\n", a);
  printbits(a);
  printbits(b);
  printf("%d\n", b);

  a = 85;
  // mask = ??? // define this mask as a macro with arguments
  b = a ^ TURN_ON_MASK(numbits, startbit);
  printf("Toggle %d bits starting at bit#%d\n", numbits, startbit);
  printf("%d\n", a);
  printbits(a);
  printbits(b);
  printf("%d\n", b);

  getchar();
  return 0;
}

/**************************************************************
Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short wrd, int bit_to_test)
{
  wrd >>= bit_to_test;
  wrd &= 1;
  return wrd;
}

/**************************************************************
This uses a trick to print an unsigned short as a string of
16 bits
*/
void printbits(unsigned short wrd)
{
  int  testbit(unsigned short wrd, int bit_to_test);
  int i;

  for (i = 15; i >= 0; i--)
  {
    printf("%1d", testbit(wrd, i));
    if (!(i % 4))
      printf(" ");
  }
  printf("\n");
  return;
}

/**************** Sample Output ****************

0000 0000 0100 0001
Turn ON 3 bits starting at bit#2
32
0000 0000 0010 0000
0000 0000 0011 1100
60
Turn OFF 3 bits starting at bit#2
31
0000 0000 0001 1111
0000 0000 0000 0011
3
Toggle 3 bits starting at bit#2
85
0000 0000 0101 0101
0000 0000 0100 1001
73


*/
