#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
  int totalMonths;
  double annualInterest, totalInterestEarned = 0.0, monthlyInterest;
  double starting_bal, ending_bal = 0.0;
	double totalMonthlyDeposit = 0.0, totalMonthlyWithdrawal = 0.0;
  double totalDeposit, totalWithdrawal, monthlyDeposit, monthlyWithdrawal;

  cout << "Enter the annual interest rate on the account (e.g. .04): ";
  cin >> annualInterest;

  cout << "\nEnter the starting balance: ";
  cin >> starting_bal;

  cout << "\nHow many months have passed since the account was established? ";
  cin >> totalMonths;

  ending_bal = starting_bal;

  for (int i = 0; i < totalMonths; i++)
  {
    cout << "\nMonth " << i+1;

		cout << "\n\tTotal deposits for this month: $";
    cin >> monthlyDeposit;
		totalMonthlyDeposit += monthlyDeposit;

		cout << "\n\tTotal withdrawals for this month: $";
    cin >> monthlyWithdrawal;
		totalMonthlyWithdrawal += monthlyWithdrawal;

		ending_bal += monthlyDeposit - monthlyWithdrawal;
		monthlyInterest = ending_bal * annualInterest/12.0;

		if (ending_bal < 0)
			break;

    ending_bal += monthlyInterest;
		totalInterestEarned += monthlyInterest;
  }

	cout << "\nReport written to Report.txt.\n" << endl;

	ofstream fout;
	fout.open("Report.txt");
  fout << setprecision(2) << fixed;
	if (ending_bal < 0)
  {
    fout << "The account has a balance of " << ending_bal << endl;
    fout << "Because the balance is negative, the account "
         << "has been closed." << endl;
  }

	fout << "\nEnding balance:" << setw(16) << "$" << ending_bal;
	fout << "\nAmount of deposits:" << setw(12) << "$" << totalMonthlyDeposit;
	fout << "\nAmount of withdrawals:" << setw(9) << "$"
       << totalMonthlyWithdrawal;
	fout << "\nAmount of interest earned:" << setw(5) << "$"
       << totalInterestEarned;
	fout.close();

  return 0;
}

