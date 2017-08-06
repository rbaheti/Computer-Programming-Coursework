#ifndef _TEAMLEADER_H_
#define _TEAMLEADER_H_
#include "ProductionWorker.h"
using namespace std;

class TeamLeader : public ProductionWorker {
public:
  TeamLeader();
  TeamLeader(string name, long id, string date, int shift, double hourlyPayRate, 
  double monthlyBonus, double requiredWorkingHours, double attendedWorkingHours);
  void SetTeamLeaderData(double monthlyBonus, double requiredWorkingHours, double attendedWorkingHours);
  double GetMonthlyBonus();
  double GetRequiredWorkingHours();
  double GetAttendedWorkingHours();
  virtual string GetDesignation();

private:
  double monthlyBonus;
  double requiredWorkingHours;
  double attendedWorkingHours;
};



#endif
