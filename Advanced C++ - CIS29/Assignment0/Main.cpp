#include <iostream>
#include "Converter.h"
using namespace std;

double RequestAction(Converter &converter);

int main() {
  Converter converter;
  double value = RequestAction(converter);
  cout << value;

  cin.get();
  cin.get();
  return 0;
}

double RequestAction(Converter &converter) {
  int conversionChoice = 1;
  double conversionValue = 0;
  double finalConversion = 0;
  int convertFrom = 1;
  int convertTo = 1;
  cout << "Enter your choice:" << endl;
  cout << "\t1. Convert English to Metric" << endl;
  cout << "\t2. Convert Metric to English" << endl;
  cin >> conversionChoice;

  cout << "Convert:" << endl;
  cout << "\t1. Distance" << endl;
  cout << "\t2. Weight" << endl;
  cout << "\t3. Volume" << endl;
  int conversionType = 1;
  cin >> conversionType;

  if (conversionChoice == 1) {
    if (conversionType == 1) {
      cout << "Convert from:\n\t1. Inch\n\t2. Foot\n\t3. Mile\n";
      cin >> convertFrom;

      cout << "Convert to:\n\t1. Centimeter\n\t2. Meter\n\t3. Kilometer\n";
      cin >> convertTo;
      convertTo += 3;
    }
    else if (conversionType == 2) {
      cout << "Convert from:\n\t1. Ounce\n\t2. Pound\n";
      cin >> convertFrom;

      cout << "Convert to:\n\t1. Gram\n\t2. Kilogram\n";
      cin >> convertTo;
      convertTo += 2;
    }
    else {
      cout << "Convert from:\n\t1. Fluid Ounce\n\t2. Gallon\n";
      cin >> convertFrom;

      cout << "Convert to:\n\t1. Milliliter\n\t2. Liter\n";
      cin >> convertTo;
      convertTo += 2;
    }
  }

  else if (conversionChoice == 2) {
    if (conversionType == 1) {
      cout << "Convert from:\n\t1. Centimeter\n\t2. Meter\n\t3. Kilometer\n";
      cin >> convertFrom;
      convertFrom += 3;

      cout << "Convert to:\n\t1. Inch\n\t2. Foot\n\t3. Mile\n";
      cin >> convertTo;
    }
    else if (conversionType == 2) {
      cout << "Convert from:\n\t1. Gram\n\t2. Kilogram\n";
      cin >> convertFrom;
      convertFrom += 2;

      cout << "Convert to:\n\t1. Ounce\n\t2. Pound\n";
      cin >> convertTo;
    }
    else {
      cout << "Convert from:\n\t1. Milliliter\n\t2. Liter\n";
      cin >> convertFrom;
      convertFrom += 2;

      cout << "Convert to:\n\t1. Fluid Ounce\n\t2. Gallon\n";
      cin >> convertTo;
      convertTo;
    }
  }
  cout << "Enter your value to be converted: ";
  cin >> conversionValue;
  switch (conversionType) {
  case 1: {
    DistanceUnit DU_From = static_cast<DistanceUnit>(convertFrom);
    DistanceUnit DU_To = static_cast<DistanceUnit>(convertTo);
    finalConversion = converter.ConvertDistance(conversionValue, DU_From, DU_To);
    return finalConversion;
  }

  case 2: {
    WeightUnit WU_From = static_cast<WeightUnit>(convertFrom);
    WeightUnit WU_To = static_cast<WeightUnit>(convertTo);
    finalConversion = converter.ConvertWeight(conversionValue, WU_From, WU_To);
    return finalConversion;
  }

  case 3: {
    VolumeUnit VU_From = static_cast<VolumeUnit>(convertFrom);
    VolumeUnit VU_To = static_cast<VolumeUnit>(convertTo);
    finalConversion = converter.ConvertVolume(conversionValue, VU_From, VU_To);
    return finalConversion;
  }
  }
}