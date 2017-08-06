// Written by A. Student
//
// Modified by: <Rashmi Baheti>
// IDE: Visual Studio 2015
//
//This program creates a linked list to store Country objects from a text file. Each object contains
//information such as the country code, name, capital, and population. The user may
//view a table of all countries and their information, delete a country from the list,
//or search for a specific country and its information.

#define _CRT_SECURE_NO_WARNINGS // needed to avoid warnings
#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string.h>  // needed for strcpy_s
#include <ctype.h>
#include "CountryList.h"

using namespace std;

#define INPUT_FILE "countries.txt"

void loadCountries(CountryList &list, const char *filename);
void requestAction(CountryList &list);
void requestSearch(CountryList &list);
void requestDeletes(CountryList &list);
void insert(CountryList &list);
void printLargestPopulation(CountryList &list);
string toUpperCase(string input);

int main()
{
  CountryList list;
  loadCountries(list, INPUT_FILE);
  requestAction(list);

  printLargestPopulation(list);
  cout << endl << "Exiting now.. Good Bye!" << endl;

  cin.get();
  return 0;
}

//***********************************************
// Builds a sorted linked list from an input file
//***********************************************
void loadCountries(CountryList &list, const char *filename)
{
  ifstream inputFile;
  Country newCountry;

  // open the input file
  inputFile.open(filename);
  if (!inputFile) {
    cout << "Error opening file \"" << filename << "\"\n";
    exit(1);
  }
  //Read each line of text into its own country object, then insert it into the list
  string code;
  while (inputFile >> code) {
    code = toUpperCase(code);
    newCountry.SetCode(code.c_str());

    //getline discards the delimiter ';' while preserving the space
    string name;
    getline(inputFile, name, ';');
    newCountry.SetName(name);

    string capital;
    getline(inputFile, capital, ';');
    newCountry.SetCapital(capital);

    //inputFile >> as opposed to getline to avoid string to int conversion
    int population;
    inputFile >> population;
    newCountry.SetPopulation(population);

    list.insertNode(newCountry);
  }
  inputFile.close();
}
//***********************************************
// Menu Manager: displays a menu
// and calls the requested function
//***********************************************
void requestAction(CountryList &list)
{
  cout << "What would you like to do?" << endl;
  string input = "1";
  do {
    cout << "1: Display countries in ascending order\n" << "2: Display countries in descending order\n" <<
      "3: Search for a country\n" << "4: Delete a country\n" << "5: Add New Country\n" <<
      "6: Search capitals with a letter\n" << "7: Exit" << endl;
    getline(cin, input);
    cout << endl;
    //If valid input, execute corresponding functionality"
    if (input == "1" || input == "2" || input == "3" || input == "4"
      || input == "5" || input == "6" || input == "7") {
      //Process input
      if (input == "1") {
        list.displayListForward();
        cout << "Number of countries in the list: " << list.getCount() << "\n\n";
      }
      if (input == "2") {
        list.displayListBackward();
        cout << "Number of countries in the list: " << list.getCount() << "\n\n";
      }
      else if (input == "3") {
        requestSearch(list);
      }
      else if (input == "4") {
        requestDeletes(list);
        cout << "Number of countries in the list: " << list.getCount() << "\n\n";
      }
      else if (input == "5") {
        insert(list);
      }
      else if (input == "6") {
        string letter;
        cout << "Please enter a letter: ";
        getline(cin, letter);
        list.findLetterInString(letter.at(0));
      }
    }
    else {
      cout << "Please enter either 1, 2, 3, 4, 5, 6 or 7" << endl;
    }
    //7 corresponds with the quit option
  } while (input != "7");
}

//***********************************************
// Search Manger: asks the user to enter a code,
// searches for that code and displays the
// information about that country or
// an error message if not found; repeats this
// process until the user enters QUIT.
//***********************************************
void requestSearch(CountryList &list) {
  string input;
  do {
    //stores the result of the list.findCountry function
    Country* country = NULL;
    cout << "Please enter the code of a country you wish to search for OR " << endl;
    cout << "Type QUIT to return to the previous page." << endl;
    getline(cin, input);
    cout << endl;

    if (toUpperCase(input) == "QUIT") {
      break;
    }

    string inputUpperCase = toUpperCase(input);

    country = list.findCountry(inputUpperCase.c_str());

    if (country) {
      // Display country information if list.findCountry returned a country class
      cout << "Found a match!" << endl;
      cout << "Country code: " << country->GetCode() << endl;
      cout << "Country name: " << country->GetName() << endl;
      cout << "Country capital: " << country->GetCapital() << endl;
      cout << "Country population: " << country->GetPopulation() << endl;
    }
    else {
      // If country is still null, display error message.
      cout << "Could not find a country with code: " << input << endl;
    }
    cout << endl;
  } while (true);
}

//***********************************************
// Delete Manger: asks the user to enter a code,
// searches for that code and deletes it or
// displays an error message if not found;
// repeats this process until the user enters QUIT.
//***********************************************
void requestDeletes(CountryList &list) {
  string input;
  do {
    //the errorCode is used to store the result of list.deleteNode to explain
    //to the user if the country was successfully deleted, if it could not be found,
    //or if the list is empty and they are wasting their time
    int errorCode;

    cout << "Please enter the code of the country you wish to delete OR " << endl;
    cout << "Type QUIT to return to the previous page" << endl;
    getline(cin, input);
    cout << endl;

    if (toUpperCase(input) == "QUIT") {
      break;
    }

    string inputUpperCase = toUpperCase(input);

    errorCode = list.deleteNode(inputUpperCase.c_str());

    if (errorCode == -1) {
      cout << "There are no countries left to delete!" << endl;
    }
    else if (errorCode == 0) {
      cout << "Could not find country with code: " << input << endl;
    }
    else if (errorCode == 1) {
      cout << input << " has been deleted." << endl << endl;
    }
    cout << endl;
  } while (true);
}

void insert(CountryList &list) {
  Country newCountry;
  string input;

  cout << "Please enter the details of the new country: " << endl << endl;
  cout << "Country Code: ";
  getline(cin, input);
  if (input.size() != 2 || isalpha(input.at(0)) == 0 || isalpha(input.at(1)) == 0) {
    cout << "Invalid input. Country code may only contain 2 alphabets." << endl << endl;
    return;
  }
  string inputUpperCase = toUpperCase(input.c_str());
  newCountry.SetCode(inputUpperCase.c_str());

  cout << "Country Name: ";
  getline(cin, input);
  newCountry.SetName(input);

  cout << "Country Capital: ";
  getline(cin, input);
  newCountry.SetCapital(input);

  cout << "Country Population: ";
  getline(cin, input);
  int population = atoi(input.c_str());
  if (population <= 0) {
    cout << "Invalid entry. Population should be a non-zero number." << endl;
    return;
  }
  newCountry.SetPopulation(population);

  Country* country = list.findCountry(newCountry.GetCode());
  if (country) {
    cout << "This country already exists. Please add new country in the list.";
    return;
  }
  list.insertNode(newCountry);
  cout << "Your country has been added to the list." << endl << endl;
}

void printLargestPopulation(CountryList &list) {
  Country* mostPopulatedCountry = NULL;

  mostPopulatedCountry = list.findCountryWithLargestPopulation();
  // Display country information with the largest population
  cout << "Country with the largest population is: " << endl;
  cout << "Country code: " << mostPopulatedCountry->GetCode() << endl;
  cout << "Country name: " << mostPopulatedCountry->GetName() << endl;
  cout << "Country capital: " << mostPopulatedCountry->GetCapital() << endl;
  cout << "Country population: " << mostPopulatedCountry->GetPopulation() << endl;
  cout << endl;
}

string toUpperCase(string input) {
  char* charInput = new char[input.size() + 1];
  strcpy(charInput, input.c_str());

  char* orig_charInput = charInput;

  while (*charInput != '\0') {
    *charInput = toupper(*charInput);
    charInput++;
  }

  // Create anonymous string object and assign it to input
  // using string class constructor : string (const char* s);
  input = string(orig_charInput);
  delete[] orig_charInput;
  return input;
}

/*****************************************************************************
******************************SAMPLE OUTPUT***********************************
******************************************************************************
What would you like to do?
1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
1

Code--Country-------------Capital------------------Population
-------------------------------------------------------------
AU            Australia            Canberra      20,90,437
BR               Brazil            Brasilia    186,112,794
BU             Bulgaria               Sofia      7,262,675
CA               Canada              Ottawa      32,805,41
CN                China             Beijing  1,306,313,812
DO   Dominican Republic       Santo Domingo       8,950,34
EG                Egypt               Cairo     77,505,756
ES                Spain              Madrid     40,341,462
FJ                 Figi                Suva        893,354
FR               France               Paris     60,656,178
GR               Greece              Athens     10,668,354
HU              Hungary            Budapest       10,6,835
IR                 Iran              Tehran      68,17,860
JA                Japan               Tokyo    127,288,419
LI        Liechtenstein               Vaduz         33,717
MC               Monaco              Monaco         32,409
MU            Mauritius          Port Louis      1,230,602
MX               Mexico         Mexico City    106,202,903
NP                Nepal           Kathmandu     27,676,547
RU               Russia              Moscow    143,420,309
TW               Taiwan              Taipei     22,894,384
US        United States       Washington DC    295,734,134

Number of countries in the list: 22

1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
2

Code--Country-------------Capital------------------Population
-------------------------------------------------------------
US        United States       Washington DC    295,734,134
TW               Taiwan              Taipei     22,894,384
RU               Russia              Moscow    143,420,309
NP                Nepal           Kathmandu     27,676,547
MX               Mexico         Mexico City    106,202,903
MU            Mauritius          Port Louis      1,230,602
MC               Monaco              Monaco         32,409
LI        Liechtenstein               Vaduz         33,717
JA                Japan               Tokyo    127,288,419
IR                 Iran              Tehran      68,17,860
HU              Hungary            Budapest       10,6,835
GR               Greece              Athens     10,668,354
FR               France               Paris     60,656,178
FJ                 Figi                Suva        893,354
ES                Spain              Madrid     40,341,462
EG                Egypt               Cairo     77,505,756
DO   Dominican Republic       Santo Domingo       8,950,34
CN                China             Beijing  1,306,313,812
CA               Canada              Ottawa      32,805,41
BU             Bulgaria               Sofia      7,262,675
BR               Brazil            Brasilia    186,112,794
AU            Australia            Canberra      20,90,437

Number of countries in the list: 22

1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
3

Please enter the code of a country you wish to search for OR
Type QUIT to return to the previous page.
US

Found a match!
Country code: US
Country name:  United States
Country capital:  Washington DC
Country population: 295734134

Please enter the code of a country you wish to search for OR
Type QUIT to return to the previous page.
quit

1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
4

Please enter the code of the country you wish to delete OR
Type QUIT to return to the previous page
us

us has been deleted.


Please enter the code of the country you wish to delete OR
Type QUIT to return to the previous page
quit

Number of countries in the list: 21

1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
5

Please enter the details of the new country:

Country Code: IN
Country Name: India
Country Capital: Delhi
Country Population: 1234567890
Your country has been added to the list.

1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
6

Please enter a letter: i
BR  Brazil;  Brasilia; 186,112,794
BU  Bulgaria;  Sofia; 7,262,675
CN  China;  Beijing; 1,306,313,812
DO  Dominican Republic;  Santo Domingo; 8,950,34
EG  Egypt;  Cairo; 77,505,756
ES  Spain;  Madrid; 40,341,462
FR  France;  Paris; 60,656,178
IN  India; Delhi; 1,234,567,890
MU  Mauritius;  Port Louis; 1,230,602
MX  Mexico;  Mexico City; 106,202,903
TW  Taiwan;  Taipei; 22,894,384

1: Display countries in ascending order
2: Display countries in descending order
3: Search for a country
4: Delete a country
5: Add New Country
6: Search capitals with a letter
7: Exit
7

Country with the largest population is:
Country code: CN
Country name:  China
Country capital:  Beijing
Country population: 1306313812

Exiting now.. Good Bye!
*/
