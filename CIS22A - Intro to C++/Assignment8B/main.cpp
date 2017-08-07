#include <iostream>
using namespace std;

const int NUM_QUESTIONS = 20;
void readInput(char []);
void showResult(int, int, int[]);

int main()
{
	char modelAns[] = {'A', 'D', 'B', 'B', 'C', 'B', 'A', 'B', 'C', 'D',
										 'A', 'C', 'D', 'B', 'D', 'C', 'C', 'A', 'D', 'B'};
	char studentAns[NUM_QUESTIONS];
	int incorrectAns[NUM_QUESTIONS];
	int correctAnsCount = 0, incorrectAnsCount = 0;

	readInput(studentAns);

  // This for loop counts the number of correct and incorrect answers.
	for (int i = 0; i < 20; i++)
	{
		if (studentAns[i] == modelAns[i])
			correctAnsCount++;
		else
		{
			incorrectAns[incorrectAnsCount] = i+1;
			incorrectAnsCount++;
		}
	}

	showResult(correctAnsCount, incorrectAnsCount, incorrectAns);

	return 0;
}

// The readInput function asks the user to enter the student’s answers for each
// of the 20 questions and then the answers are stored in another array.
void readInput(char studentAns[])
{
	cout << "Please enter your answers: \n";
	for (int i = 0; i < NUM_QUESTIONS; i++)
	{
		cout << i + 1 << ". ";
		cin >> studentAns[i];
		while (studentAns[i] != 'A' && studentAns[i] != 'B' &&
					 studentAns[i] != 'C' && studentAns[i] != 'D')
		{
			cout << "Invalid Entry. Your answer should be A through D only.\n";
			cout << i+1 << ". ";
			cin >> studentAns[i];
		}
	}
}


// The showResult function displays a message indicating whether the student
// passed or failed the exam. It then displays the total number of correctly
// and incorrectly answered questions and a list showing the question numbers
// of the incorrectly answered questions.
void showResult(int correctAnsCount, int incorrectAnsCount, int incorrectAns[])
{
	if (correctAnsCount >= 15)
		cout << "\nCongratulations! You have passed the test." << endl;

	else
		cout << "\nSorry! You have not passed the test." << endl;

	cout << "You have " << correctAnsCount << " correctly answered questions and "
       << incorrectAnsCount << " incorrectly answered questions." << endl;

	if (incorrectAnsCount > 0)
	{
		cout << "\nYour answers were incorrect for question numbers: \n";
		for (int i = 0; i < incorrectAnsCount; i++)
		cout << incorrectAns[i] << " ";
	}
	cout << endl;
}


