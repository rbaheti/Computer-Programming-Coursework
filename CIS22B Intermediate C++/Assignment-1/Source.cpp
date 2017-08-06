/*
Course    : CIS 22B
Lab_No 01 : Read a file then sorting it using selection sort and searching a word in the file using Binary search.
Name      : 1. Rashmi Baheti
	        2. Joshua Bowen
*/

/*
Pseudocode:
Define a recursive function for selection sort:
Input : Array arr[] to sort, Size of array arr[], Index 'i' in the array from where the array needs to be sorted.
Check the condition : If no more numbers are left for sorting then return.

Now, find the lowest number in the array arr[] using variables i and j.
	Once the lowest number is found, send it to the 1st element of the array.
		Similarly, find the lowest number from the remaining unsorted array arr[] and
		send it to the 2nd element in the array.
		In this way, sort all the remaining elements in the array in the ascending order.
		(This is done by calling the search function to itself until  no more numbers are left for sorting).

Define a void function "printWords()" to print the array elements:
Input : Array arr[] of string datatype, No. of words "numWords" of integer datatype.
For integer i is set to each subscript in array from 0 through the next-to-last subscript.
	Then printing the value of each element in the array arr[].

Define binary search function "binarySearch()" to search the user word.
Input : Array arr[] to search the word in it, first

*/


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
	cout << "Please open Assignment1_Que.txt file." << endl;
	
	ifstream infile;
	string arr[1024];
	int numWords = 0;
	infile.open("Assignment1_Que.txt");
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