/** Name          : Rashmi Omprakash Baheti
    Date          : 27th July 2015
    Assignment 9  : Option A
    Program Title : This program asks the user to enter a phrase, sentence or
                    paragraph. Reads it in as a string, then reports back to
                    the user by displaying the following:
                    1.The user’s string all up-cased
                    2.The user’s string all down-cased
                    3.Report the number of vowels in the input string
                    4.Report the numbers of Consonants in the input string.
                    5.The user’s string in reverse order
**/

#include <iostream>
using namespace std;

int main()
{
  string userString, resultString;
  int vowelCount = 0, consonantsCount = 0, strLength;

  cout << "Please enter a phrase, sentence or a paragraph:" << endl;
  getline(cin, userString);
  cout << endl;
  resultString = userString;
  strLength = userString.length();
  for (int i = 0; i < strLength; i++)
  {
    resultString[i] = toupper(userString.at(i));
    cout << resultString[i];
  }
  cout << endl;

  for (int i = 0; i < strLength; i++)
  {
    resultString[i] = tolower(userString.at(i));
    cout << resultString[i];
    if (resultString[i] == 'a' || resultString[i] == 'e' ||
        resultString[i] == 'i' || resultString[i] == 'o' ||
        resultString[i] == 'u')
      vowelCount++;
    else
      consonantsCount++;
  }

  cout << endl;
  cout << "Numbers of Vowels: " << vowelCount << endl;
  cout << "Numbers of Consonants: " << consonantsCount << endl;

  resultString = userString;
  int index = strLength;
  for (int i = 0; i < strLength ; i++)
  {
    resultString[i] = userString.at(index-1);
    cout << resultString[i];
    index--;
  }

  return 0;
}
