#include<iostream>
using namespace std;

int main()
{
	char ch[50];
	int count[5] = { 0 }, size = 0;
	char mychar[5] = { 0 };
	cout << "Please enter characters from 'A' to 'E' upto 50 count or less." <<  endl;
	cout << "Enter -1 when you are done" << endl;

	for (int i = 0; i < 50; i++)
	{
		cin >> ch[i];
		if (ch[i] >= 'A' && ch[i] <= 'E')
		{			
			size++;
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < size; i++)
	{
		count[ch[i] - 'A']++;
		mychar[ch[i] - 'A'] = ch[i];
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < count[i]; j++)
		{
			cout << mychar[i] << " ";
		}
		cout << endl;
	}
	getchar();
	getchar();
	return 0;
}