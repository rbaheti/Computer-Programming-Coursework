/** Name          : Rashmi Omprakash Baheti
    Date          : 9th July 2015
    Assignment    : Option B
    Program Title : Program that calculates a customer’s monthly phone bill **/


#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    char choice;
    double minutes, totalBill = 0;

    cout << "Lets calculate your monthly phone bill!\n";
    cout << "Which package have you purchased ?\n";
    cout << "1. Package A\n";
    cout << "2. Package B\n";
    cout << "3. Package C\n";
    cout << "Please enter package name A, B or C \n";
    cin >> choice;

    cout << "How many minutes have you used?\n";
    cin >> minutes;

    switch (choice)
    {
        case 'a':
        case 'A': totalBill = 39.99;
                  if (minutes > 450)
                     totalBill += ((minutes - 450) * 0.45);
                  break;

        case 'b':
        case 'B': totalBill = 59.99;
                  if (minutes > 900)
                     totalBill += ((minutes - 900) * 0.40);
                  break;

        case 'c':
        case 'C': totalBill = 69.99;
                  break;

        default: cout << "\nInvalid entry in your package name. Please try again.\n";
    }

    if (totalBill > 0)
        cout << setprecision(2) << fixed << "\nTotal amount due is " << totalBill << "$\n";

    return 0;
}
