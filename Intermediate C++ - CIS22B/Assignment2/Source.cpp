#include <iostream>
using namespace std;

int stringLength(const char * str);
char * stringNCopy(char * destination, const char * source, int num);
char * stringAdd(char * destination, const char * source);

int main()
{
	char choice_str[10];
	int choice;
	cout << "What would you like to do with your string?" << endl;
	cout << "Please enter numbers 1 through 5." << endl;
	cout << "1. Calculate length of the string" << endl;
	cout << "2. Copy one string into another string" << endl;
	cout << "3. Add two strings " << endl;
	cout << "4. Compare two strings" << endl;
	cout << "5. Exit." << endl << endl;
	cin.getline(choice_str, 10);
	if (strlen(choice_str) != 1 || !isdigit(choice_str[0])) {
		choice = 6;
	}
	else {
		choice = atoi(choice_str);
	}

	switch(choice)
	{
		case 1:
			char str[100];
			cout << "Please enter your string : ";
			cin.getline(str, 100);
			cout << "The length of your string is: " << stringLength(str) << endl;
			break;

		case 2: {
			char destination[100], source[100];
			int num;
			cout << "Please enter your string to be copied: ";
			cin.getline(source, 100);
			cout << "Please enter the max number of characters to be copied: ";
			cin >> num;
			cout << "The copied string is: " << stringNCopy(destination, source, num) << endl;
			break; }

		case 3: 
			char destination[100], source[100];
			break;

		case 4:
			break;

		case 5:
			break;

		default:
			cout << "Invalid entry. Please try again!" << endl;
			break;
	}

	cin.get();
	cin.get();
	return 0;
}

int stringLength(const char * str)
{
	int i = 0;
	while (*(str + i) != NULL)
	{
		i++;
	}
	return i;
}

char * stringNCopy(char* destination, const char* source, int num)
{
	int i = 0;
	while (i < num && (*(source + i) != NULL))
	{
		*(destination + i) = *(source + i);
		i++;
	}

	*(destination + i) = NULL;
	return destination;
}