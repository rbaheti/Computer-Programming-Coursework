#include <iostream>
using namespace std;
int SIZE = 8;

void bubbleSort(int arr[], int SIZE)
{
	bool swap;
	int index;
	do
	{
		swap = false;
		for (index = 0; index < (SIZE - 1); index++)
		{
			if (arr[index] > arr[index + 1])
			{
				int temp = arr[index];
				arr[index] = arr[index + 1];
				arr[index + 1] = temp;
				swap = true;
			}
		}
	} while (swap);

	for (index = 0; index < SIZE; index++)
	{
		cout << arr[index] << " ";
	}
}

void selectionSort(int arr[], int SIZE, int i, int j)
{
	int temp;
	if (i < SIZE - 1)
	{
		if (j < SIZE)
		{
			if (arr[j] < arr[i])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			selectionSort(arr, SIZE, i, j + 1);
		}
		selectionSort(arr, SIZE, i + 1, i + 2);
	}
}
int main()
{
	int arr[] = { 10, 15, 6, 80, 64, 9, 1, 50 };
	int 
		
		index = 0;
	cout << "The unsorted array is: \n";
	for (index = 0; index < SIZE; index++)
	{
		cout << arr[index] << " ";
	}
	cout << endl;

	//cout << "Now, the sorted array using BUBBLE SORT in ascesnding order is: \n";
	//bubbleSort(arr, SIZE);

	cout << "\nNow, the sorted array using SELECTION SORT in ascesnding order is: \n";
	selectionSort(arr, SIZE, 0, 1);
	for (int index = 0; index < SIZE; index++)
	{
		cout << arr[index] << " ";
	}

	getchar();
	return 0;
}