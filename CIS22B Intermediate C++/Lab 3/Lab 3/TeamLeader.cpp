#include "TeamLeader.h"
#include <iostream>

using namespace std;

TeamLeader::TeamLeader() {
  monthlyBonus = 0;
  requiredWorkingHours = 0;
  attendedWorkingHours = 0;
}

TeamLeader::TeamLeader(string name, long id, string date, int shift, double hourlyPayRate,
  double monthlyBonus, double requiredWorkingHours, double attendedWorkingHours)
  :ProductionWorker(name, id, date, shift, hourlyPayRate) {
  this->monthlyBonus = monthlyBonus;
  this->requiredWorkingHours = requiredWorkingHours;
  this->attendedWorkingHours = attendedWorkingHours;
}

void TeamLeader::SetTeamLeaderData(double mBonus, double reqWorkingHours, double attndWorkingHours) {
  monthlyBonus = mBonus;
  requiredWorkingHours = reqWorkingHours;
  attendedWorkingHours = attndWorkingHours;
}

double TeamLeader::GetMonthlyBonus() {
  return monthlyBonus;
}

double TeamLeader::GetRequiredWorkingHours() {
  return requiredWorkingHours;
}

double TeamLeader::GetAttendedWorkingHours() {
  return attendedWorkingHours;
}

string TeamLeader::GetDesignation() {
  return "Team Leader";
}