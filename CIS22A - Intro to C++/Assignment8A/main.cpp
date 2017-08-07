#include <iostream>
using namespace std;

// Calling a function
void displayGreaterNums(int [], int , int);

int main()
{
	const int SIZE = 10;
	int array[SIZE], num;

	cout << "Enter 10 integers: \n";
	for (int i = 0; i < 10; ++i)
	{
		cin >> array[i];
	}

	cout << "Enter a number: ";
	cin >> num;

	displayGreaterNums(array, SIZE, num);

	return 0;
}


// The displayGreaterNums function finds and displays all of the
// numbers in the array that are greater than the input number.

void displayGreaterNums(int array[], int size, int num)
{
	bool foundGreaterNums = false;
	for (int i = 0; i < size; i++)
	{
		if (array[i] > num)
		{
			foundGreaterNums = true;
			break;
    }
	}

	if (!foundGreaterNums)
		cout << "There is not any number greater than " << num << " in your array";
	else
	{
		cout << "Numbers greater than " << num <<" in your array of integers are:";
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			if (array[i] > num)
			cout << array[i] << " ";
		}
	}
	cout << endl;
	return;
}

