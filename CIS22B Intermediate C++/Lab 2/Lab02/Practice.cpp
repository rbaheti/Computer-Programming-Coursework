/*#include <iostream>
using namespace std;

int stringLength(const char * str);

int main1()
{
	char str[100];
	int i = 0;
	cout << "Please enter your string and I will calculate its length." << endl;
	cin.getline(str, 100);
	
	cout << "The length of your string is: " << stringLength(str) << endl;

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

*/