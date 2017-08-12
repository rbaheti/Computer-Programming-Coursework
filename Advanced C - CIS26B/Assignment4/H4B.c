#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Fuction prototypes.
void menu();
int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);
unsigned short overlay(unsigned short wrd, int startbit, int numbits, unsigned short pattern);
void menuChoice9(unsigned short wrd);

// Macros
#define TURN_ON_MASK(numbits, startbit) ((~(((unsigned short)~0) << numbits)) << startbit);
#define TURN_OFF_MASK(numbits, startbit) (~((~(((unsigned short)~0) << numbits)) << startbit));

int main(void)
{
  menu();

  getchar();
  return 0;
}

/**************************************************************
menu() presents program menu to the user to let the user control
theater lights.
*/
void menu()
{
  while (1) {
    printf("\n1) Turn on all lights\n");
    printf("2) Turn on center stage lights(lights 5 - 10)\n");
    printf("3) Turn on left stage lights(lights 11 - 15)\n");
    printf("4) Turn on right stage lights(lights 0 - 4)\n");
    printf("5) Turn off all lights\n");
    printf("6) Turn off center stage lights\n");
    printf("7) Turn off left stage lights\n");
    printf("8) Turn off right stage lights\n");
    printf("9) Enter on / off pattern\n");
    printf("10) Quit the menu\n");
    printf("Enter menu choice: ");

    char inputStr[100];
    gets(inputStr);

    // Remove leading spaces, if any, in the user given string.
    int ignore_leading_spaces = strspn(inputStr, " \t");
    strcpy(inputStr, inputStr + ignore_leading_spaces);

    // Check for valid user input.
    const int inputStrlength = strlen(inputStr);
    if (inputStrlength >= 2 && strcmp(inputStr, "10") != 0) {
      int digit_span = strspn(inputStr, "0123456789");
      if (!digit_span) {
        printf("Illegal menu selection! Try again!\n");
        continue;
      }

      char postInputStr[100];
      strcpy(postInputStr, inputStr + digit_span);

      int ignore_leading_spaces = strspn(postInputStr, " \t");
      strcpy(postInputStr, postInputStr + ignore_leading_spaces);

      if (postInputStr[0] != '\0') {
        if (ignore_leading_spaces > 0) {
          printf("Only one menu selection allowed! Try again!\n\n");
        }
        else {
          printf("Illegal menu selection! Try again!\n\n");
        }
        continue;
      }
    }
    char *pEnd;
    long integerInput = 0;
    integerInput = strtol(inputStr, &pEnd, 10);
    if (integerInput < 1 || integerInput > 10) {
      printf("Please enter integer value 1 through 10 only!\n");
      continue;
    }

    unsigned short wrd = 0; // all lights are off by-default. 
    int numbits = 0;
    int startbit = 0;

    switch (integerInput) {
    case 1: // turn ON all lights.
    {
      wrd = ~0;
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 2: // turn on center stage lights (lights 5-10)
    {
      numbits = 6;
      startbit = 5;
      wrd = TURN_ON_MASK(numbits, startbit);
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 3: // turn on left stage lights (lights 11-15)
    {
      numbits = 5;
      startbit = 11;
      wrd = TURN_ON_MASK(numbits, startbit);
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 4:  // turn on right stage lights(lights 0 - 4)
    {
      numbits = 5;
      startbit = 0;
      wrd = TURN_ON_MASK(numbits, startbit);
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 5:  // turn off all lights
    {
      wrd = 0;
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 6:  // turn off center stage lights
    {
      numbits = 6;
      startbit = 5;
      wrd = TURN_OFF_MASK(numbits, startbit);
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 7:  // turn off left stage lights
    {
      numbits = 5;
      startbit = 11;
      wrd = TURN_OFF_MASK(numbits, startbit);
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 8:  // turn off right stage lights
    {
      numbits = 5;
      startbit = 0;
      wrd = TURN_OFF_MASK(numbits, startbit);
      printf("Light settings: ");
      printbits(wrd);
    }
    break;

    case 9:  // overlay on/off pattern onto light configuration
    {
      menuChoice9(wrd);
    }
    break;

    case 10:
    {
      printf("Exiting now..\n");
      return;
    }

    default:
      printf("Invalid input!\n");
    }
  }
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
    if ((i == 5) || (i == 11))
      printf(" ");
  }
  printf("\n");
  return;
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
Overlays bit pattern in "pattern" on "wrd" and returns it.
*/
unsigned short overlay(unsigned short wrd, int startbit, int numbits, unsigned short pattern)
{
  wrd &= ~(~((unsigned short)~0 << numbits) << startbit);
  wrd |= pattern << startbit;
  return wrd;
}

void menuChoice9(unsigned short wrd) {
  while (1)
  {
    printf("Enter starting light number and on/off pattern: ");
    char orig_user_input_str[50], input_validation_str[50];
    gets(orig_user_input_str);

    // Remove leading spaces, if any, in the user given string.
    int ignore_leading_spaces = strspn(orig_user_input_str, " \t");
    strcpy(orig_user_input_str, orig_user_input_str + ignore_leading_spaces);

    if (orig_user_input_str[0] == '\0') {
      break;
    }

    strcpy(input_validation_str, orig_user_input_str);
    char* endp;
    int digit_span_check = strspn(input_validation_str, "0123456789");
    if (digit_span_check == 0) {
      printf("Illegal starting light number! Try again!\n\n");
      continue;
    }

    int startbit = strtol(input_validation_str, &endp, 10);
    if (startbit < 0 || startbit > 15) {
      printf("Illegal starting light number!\n");
      printf("Your starting light number should be between 0 to 15. Try again!\n\n");
      continue;
    }

    int whitespace_span_check = strspn(endp, " \t");
    if (whitespace_span_check == 0) {
      printf("You did not enter a bit pattern! Try again!\n\n");
      continue;
    }

    digit_span_check = strspn(endp + whitespace_span_check, "01");
    if (digit_span_check == 0) {
      printf("Illegal on/off pattern! Try again!\n\n");
      continue;
    }
    if (digit_span_check > (16 - startbit)) {
      printf("Illegal on/off pattern! Try again!\n\n");
    }

    unsigned short pattern = 0;
    pattern = strtol(endp + whitespace_span_check, &endp, 2);
    int numbits = digit_span_check;

    whitespace_span_check = strspn(endp, " \t");
    int check_extra_input_elements = strcspn(endp + whitespace_span_check, " \t");
    if (check_extra_input_elements != 0) {
      printf("Too many entries on line! Try again!\n\n");
      continue;
    }

    wrd = overlay(wrd, startbit, numbits, pattern);
    printf("Light settings: ");
    printbits(wrd);
    break;
  }
}


/********************* Sample Output ********************

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 1 3
Only one menu selection allowed! Try again!


1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 1
Light settings: 11111 111111 11111

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 3
Light settings: 11111 000000 00000

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: hg 3
Illegal menu selection! Try again!

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 3x
Illegal menu selection! Try again!

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 8
Light settings: 11111 111111 00000

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 9
Enter starting light number and on/off pattern: as
Illegal starting light number! Try again!

Enter starting light number and on/off pattern: 5 11 gf
Too many entries on line! Try again!

Enter starting light number and on/off pattern: 5 101010
Light settings: 00000 101010 00000

1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 9
Enter starting light number and on/off pattern:


1) Turn on all lights
2) Turn on center stage lights(lights 5 - 10)
3) Turn on left stage lights(lights 11 - 15)
4) Turn on right stage lights(lights 0 - 4)
5) Turn off all lights
6) Turn off center stage lights
7) Turn off left stage lights
8) Turn off right stage lights
9) Enter on / off pattern
10) Quit the menu
Enter menu choice: 10
Exiting now..

*/
