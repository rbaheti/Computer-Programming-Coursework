#include "ProductionWorker.h"
#include <iostream>

ProductionWorker::ProductionWorker() {
  shift = 0;
  hourlyPayRate = 0.0;
}

ProductionWorker::ProductionWorker(string name, long id, string date, int shift, double hourlyPayRate)
  : Employee(name, id, date) {
  this->shift = shift;
  this->hourlyPayRate = hourlyPayRate;
}

void ProductionWorker::setProductionWorkerData(int shift, double hourlyPayRate) {
  this->shift = shift;
  this->hourlyPayRate = hourlyPayRate;
}

int ProductionWorker::GetProductionWorkerShift() {
  return shift;
}

double ProductionWorker::GetProductionWorkerPayRate() {
  return hourlyPayRate;
}

string ProductionWorker::GetDesignation() {
  return "Production Worker";
}