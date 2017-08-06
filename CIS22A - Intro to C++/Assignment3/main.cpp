/**
    Name          : Rashmi Omprakash Baheti
    Date          : 8th July 2015
    Assignment 3  : Option A
    Program Title : To calculate calories of a person
                    from the given data
**/


#include <iostream> // Including input-output header file
#include <iomanip>  // Including input-output manipulative header file

using namespace std;

int main()
{
    double caloriesBurnt, weightInPound, MET, minutes;

    cout << "Welcome to the calorie calculator.\n";
    cout << "Enter your weight in pounds:\n";
    cin >> weightInPound;

    cout << "Enter the number of METs for the activity:\n";
    cin >> MET;

    cout << "Enter the number of minutes spent exercising:\n";
    cin >> minutes;

    const double weightInKg = (weightInPound / 2.2);
    // calculating total calories burnt:
    caloriesBurnt = 0.0175 *  MET * weightInKg * minutes;

    cout << setprecision(2) << fixed << "You burned an estimated ";
    cout << caloriesBurnt << " calories.\n";  // Printing the output

    return 0;
}
