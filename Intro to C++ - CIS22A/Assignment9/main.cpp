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
