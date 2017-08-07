#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void selectionSort(string arr[], int numWords, int i)
{
	if (i >= numWords - 1)
	{
		return;
	}

	for (int j = i + 1; j < numWords; j++)
	{
		if (arr[j] < arr[i]) 
		{
			string temp;
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
		}
	}
	selectionSort(arr, numWords, i+1);
}

void printWords(string arr[], int numWords)
{
	for (int i = 0; i < numWords; i++)
	{
		cout << arr[i] << endl;
	}
}

int binarySearch(string arr[], int first, int last, string search)
{
	int middle;

	if (first > last)
	{
		return -1;
	}
	middle = (first + last) / 2;
	if (arr[middle] == search)
	{
		return (middle + 1);
	}
	if (arr[middle] > search)
	{
		last = middle - 1;
	}
	else
	{
		first = middle + 1;
	}
	return binarySearch(arr, first, last, search);
}

int main()
{
	cout << "Opening input.txt file." << endl;
	
	ifstream infile;
	string arr[1024];
	int numWords = 0;
	infile.open("input.txt");
	while (!infile.eof())
	{
		infile >> arr[numWords];
		if (arr[numWords].size() > 1)
		{
			numWords++;
		}
	}
	cout << "\n\nWordCount: " << numWords << endl;

	selectionSort(arr, numWords, 0);

	cout << "Sorted words are: ";
	printWords(arr, numWords);

	cout << "Please enter your word to search: \n";
	string search;
	cin >> search;
	int position = binarySearch(arr, 0, numWords - 1, search);

	if (position == -1)
	{
		cout << "Sorry, entered word is not in the file.\n";
	}
	else
	{
		cout << "The word is at " << position << " position " << endl;
	}
	infile.close();
	system("paused");
	system("paused");
	return 0;
}