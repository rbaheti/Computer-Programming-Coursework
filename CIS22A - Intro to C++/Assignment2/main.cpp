#include <iostream>
using namespace std;

int main()
{
    int height = 6, inch = 3;   // Declaring and initializing variables, where height is in feet
    float idealBodyWeight;      // Declaring a variable to store the ideal body weight
    idealBodyWeight = 110 + ((6-5) * 12 + 3 ) * 5;  // Calculating and storing the ideal body weight in a variable idealBodyWeight
    cout << "The ideal weight for 6 feet and 3 inches body is " << idealBodyWeight << " pounds" << endl; // Printing the value
    return 0;
}
