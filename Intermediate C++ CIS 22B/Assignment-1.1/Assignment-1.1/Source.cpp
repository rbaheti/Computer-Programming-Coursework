#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void selectionSort(string[], int, int);
int binarySearch(string[], int, int, string);

int main()
{
	string infilename, outfilename, search;
	string arr[1024];
	int numWords = 0;

	cout << "Please enter the name you would like to save the program output as: " << endl;
	cin >> outfilename;

	ofstream outfile(outfilename.c_str());	

	outfile << "Please enter the name you would like to save the program output as: " << endl;
	outfile << outfilename;

	cout << endl << "Please enter the name of the text file you would like to open." << endl;
	outfile << endl << "Please enter the name of the text file you would like to open." << endl;
	cout << "(The file must be in the program folder and include the .txt suffix.)" << endl;
	outfile << "(The file must be in the program folder and include the .txt suffix.)" << endl;
	cin >> infilename;
	outfile << infilename;

	/*for (int i = 0; i < 1025; i++)
	{
		cout << arr[i] << " ";
		//.get();
		cin.get();
		cout << "Words in the file should not exceed 1024 count limit!";
	}
	cout << endl;*/

	if (infilename == outfilename)
	{
		cout << "The input file cannot be the same as the output file." << endl;
		outfile << "The input file cannot be the same as the output file." << endl;
		cout << "Program ending." << endl << endl;
		outfile << "Program ending." << endl << endl;

		cin.get();
		cin.get();
		return 0;
	}

	ifstream infile;
	infile.open(infilename.c_str());


	if (!infile.is_open())
	{
		cout << "Could not find the specified file." << endl;
		outfile << "Could not find the specified file." << endl;
		cout << "Program ending." << endl << endl;
		outfile << "Program ending." << endl << endl;

		cin.get();
		cin.get();
		return 0;
	}

  // loop continues until it reaches eof.
	while (!infile.eof()) 
	{
		infile >> arr[numWords];
		if (arr[numWords].size() > 1)
		{
			numWords++;
		}
	}
	if (numWords <= 1024)
	{
		cout << "\n\nWordCount: " << numWords << endl;
		outfile << "\n\nWordCount: " << numWords << endl;
	}
	else
	{
		cout << "Your file has more than 1024 words." << endl;
		outfile << "Your file has more than 1024 words." << endl;
		cout << "Program ending." << endl << endl;
		outfile << "Program ending." << endl << endl;

		cin.get();
		cin.get();
		return 0;
	}
	
	// Calling selection sort function
	selectionSort(arr, numWords, 0);

	//Printing the sorted words in the file named "sorted_Words.txt"
	ofstream  fsort("sorted_Words.txt");

	for (int i = 0; i < numWords; i++)
	{
		fsort << arr[i] << endl;
	}

	for (int i = 0; i < numWords; i++)
	{
		outfile << arr[i] << " ";

		for (int count = (i + 1); (count % 19) == 0; count++)
			outfile << endl;
	}
	outfile << endl;

	while (search != "x" && search != "X")
	{
		cout << "Please enter your word to search: \n";
		outfile << "Please enter your word to search: \n";

		cin >> search;
		outfile << search << endl;

		if (search != "x" && search != "X")
		{
			int position = binarySearch(arr, 0, numWords - 1, search);

			if (position == -1)
			{
				cout << "Sorry, entered word is not in the file.\n\n";
				outfile << "Sorry, entered word is not in the file.\n\n";
			}
			else
			{
				cout << "The word is at position " << position << "." << endl << endl;
				outfile << "The word is at position " << position << "." << endl << endl;
			}
		}

		cout << "Please enter x to end search.\nOr" << endl;
		outfile << "Please enter x to end search.\nOr" << endl;

		if (search == "x" || search == "X")
		{
			cout << "Ending program." << endl;
			outfile << "Ending program." << endl;

			cin.get();
			cin.get();
			return 0;
		}
	}

	infile.close();
	outfile.close();

	cin.get();
	cin.get();

	return 0;
}

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
	selectionSort(arr, numWords, i + 1);
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