#include <iostream> // Including input-output header file
#include <iomanip>  // Including input-output manipulative header file

using namespace std;

int main()
{
    double caloriesBurnt, weightInPound, minutes;
    int MET;

    cout << "Welcome to the calorie calculator.\n\n";
    cout << "Enter your weight in pounds:\n";
    cin >> weightInPound;

    cout << "Enter the number of minutes spent exercising:\n";
    cin >> minutes;

    // Displaying menu of exercises to the user:
    cout << "Select the name of your exercise by selecting its number:\n";
    cout << "1. Running\n";
    cout << "2. Basketball\n";
    cout << "3. Sleeping\n";
    cout << "4. Quit\n";

    int exerciseNumber;
    cin >> exerciseNumber;

    const double WEIGHT_IN_KG = (weightInPound / 2.2);
    const double CONSTANT_MULTIPLIER = 0.0175;
    cout << setprecision(2) << fixed;

    switch (exerciseNumber)
    {
        case 1:
            MET = 10;
            caloriesBurnt = CONSTANT_MULTIPLIER * MET * WEIGHT_IN_KG * minutes;
            cout << "You burned an estimated " << caloriesBurnt;
            cout << " calories.\n";
            break;

        case 2:
            MET = 8;
            caloriesBurnt = CONSTANT_MULTIPLIER * MET * WEIGHT_IN_KG * minutes;
            cout << "You burned an estimated " << caloriesBurnt;
            cout << " calories.\n";
            break;

        case 3:
            MET = 1;
            caloriesBurnt = CONSTANT_MULTIPLIER * MET * WEIGHT_IN_KG * minutes;
            cout << "You burned an estimated " << caloriesBurnt;
            cout << " calories.\n";
            break;

        case 4:
             cout << "Thank you! See you soon.\n";
             break;

        default :
            cout << "The valid choices are 1 through 4. Run the\n";
            cout << "program again and select one of those.\n";

    }

    return 0;
}
