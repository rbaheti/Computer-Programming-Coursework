#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int choice;

	double minutes, totalBill_A = 0, totalBill_B = 0, totalBill_C = 0;

    const float FIXED_PRICE_A = 39.99,
                FIXED_PRICE_B = 59.99,
                FIXED_PRICE_C = 69.99;

    const int FIXED_MINUTES_A = 450,
              FIXED_MINUTES_B = 900;

    const float ADDITIONAL_A = 0.45,
                ADDITIONAL_B = 0.40;

    const int PACKAGE_A = 1,
              PACKAGE_B = 2,
              PACKAGE_C = 3,
              QUIT = 4;

    cout << "Select a subscription package:\n";
    cout << "1. Package A\n";
    cout << "2. Package B\n";
    cout << "3. Package C\n";
    cout << "4. Quit \n";
    cout << "Please enter package number 1 through 3 \n";
    cout << "and enter 4 to quit: \n";
    cin >> choice;

    cout << "How many minutes have you used?\n";
    cin >> minutes;

	cout << setprecision(2) << fixed;

    switch (choice)
    {
        case PACKAGE_A: totalBill_A = FIXED_PRICE_A;
						if (minutes > FIXED_MINUTES_A)
						{
							totalBill_A += ((minutes - FIXED_MINUTES_A) * ADDITIONAL_A);
						}

                        break;

        case PACKAGE_B: totalBill_B = FIXED_PRICE_B;
                        if (minutes > FIXED_MINUTES_B)
                            totalBill_B += ((minutes - FIXED_MINUTES_B) * ADDITIONAL_B);
                        break;

        case PACKAGE_C: totalBill_C = FIXED_PRICE_C;
						cout << "\nTotal amount due is " << totalBill_C << "$\n";

			            if (minutes > FIXED_MINUTES_A)
						{
							totalBill_A += ((minutes - FIXED_MINUTES_A) * ADDITIONAL_A);
							totalBill_C = totalBill_C - FIXED_PRICE_A - totalBill_A;
                            cout << "Savings with Package A: $ " << totalBill_C;
						}
						else
                        {
                            totalBill_C = totalBill_C - FIXED_PRICE_A;
                            cout << "Savings with Package A: $ " << totalBill_C;
                        }

                        totalBill_C = FIXED_PRICE_C;
						if (minutes > FIXED_MINUTES_B)
                        {
                            totalBill_B += ((minutes - FIXED_MINUTES_B) * ADDITIONAL_B);
                            totalBill_C = totalBill_C - FIXED_PRICE_B - totalBill_B;
                            cout << "\nSavings with Package B: $ " << totalBill_C;
                        }
                        else
                        {
                            totalBill_C = totalBill_C - FIXED_PRICE_B;
                            cout << "\nSavings with Package B: $ " << totalBill_C << endl;
                        }

                        break;

        case QUIT: cout << "Thank you! See you soon.\n";
                   break;

        default: cout << "\nThe valid choices are 1 through 4. Run the \n ";
                 cout << "program again and select one of those.\n";
    }

    return 0;
}
