/** Name          : Rashmi Omprakash Baheti
    Date          : 23rd July 2015
    Assignment 7  : Option A
    Program Title : This program calculates a contestant’s score in a
                    particular talent competition.

**/

#include <iostream>
#include <iomanip>
using namespace std;

// Function prototypes
void getJudgeData(double &);
void calcScore(double, double, double, double, double);
double findLowest(double, double, double, double, double);
double findHighest(double, double, double, double, double);

int main()
{
  double score1, score2, score3, score4, score5;

  // Function calls
  getJudgeData(score1);
  getJudgeData(score2);
  getJudgeData(score3);
  getJudgeData(score4);
  getJudgeData(score5);

  calcScore(score1, score2, score3, score4, score5);

  cout << "Press any key to continue." << endl;

  return 0;
}

void getJudgeData(double &score)
{
  cout << "Enter a judge's score: ";
  cin >> score;

  while (score < 0 || score > 10)
  {
    cout << "Invalid score. Please try again." << endl;
    cout << "Enter a judge's score: ";
    cin >> score;
  }
}

void calcScore(double score1, double score2,
               double score3, double score4,
               double score5)
{
  double average, lowest, highest;

  lowest = findLowest(score1, score2, score3, score4, score5);

  highest = findHighest(score1, score2, score3, score4, score5);

  average = (score1 + score2 + score3 +
             score4 + score5 - lowest - highest)/3.0;

  cout << setprecision(1) << fixed;
  cout << "\nAfter dropping the lowest and highest scores,"
          "the average score was " << average << endl;
}

double findLowest(double score1, double score2,
                  double score3, double score4,
                  double score5)
{
  double lowest;

  if(score1 <= score2 && score1 <= score3 &&
     score1 <= score4 && score1 <= score5)
    lowest = score1;

  else if(score2 <= score1 && score2 <= score3 &&
          score2 <= score4 && score2 <= score5)
    lowest = score2;

  else if(score3 <= score1 && score3 <= score2 &&
          score3 <= score4 && score3 <= score5)
    lowest = score3;

  else if(score4 <= score1 && score4 <= score2 &&
          score4 <= score3 && score4 <= score5)
    lowest = score4;

  else
    lowest = score5;

  return lowest;
}

double findHighest(double score1, double score2,
                   double score3, double score4,
                   double score5)
{
  double highest;
  if(score1 >= score2 && score1 >= score3 &&
     score1 >= score4 && score1 >= score5)
    highest = score1;

  else if(score2 >= score1 && score2 >= score3 &&
          score2 >= score4 && score2 >= score5)
    highest = score2;

  else if(score3 >= score1 && score3 >= score2 &&
          score3 >= score4 && score3 >= score5)
    highest = score3;

  else if(score4 >= score1 && score4 >= score2 &&
          score4 >= score3 && score4 >= score5)
    highest = score4;

  else
    highest = score5;

  return highest;
}
