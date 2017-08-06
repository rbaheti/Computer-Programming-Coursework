#include "Converter.h"
#include "iostream"
using namespace std;

double Converter::ConvertDistance(int input_value, DistanceUnit input_wt_unit, DistanceUnit output_wt_unit) {
  double inch = 0, cm = 0;
  switch (input_wt_unit) {
  case INCH:
    inch = input_value;
    break;
  case FOOT:
    inch = input_value * 12.0;
    break;
  case MILE:
    inch = input_value * 12.0 * 5280;
    break;
  case CENTIMETER:
    cm = input_value;
    break;
  case METER:
    cm = input_value * 100.0;
    break;
  case KILOMETER:
    cm = 100.0 * input_value * 1000;
    break;
  }

  switch (output_wt_unit) {
  case INCH:
    return (cm / 2.54);
  case FOOT:
    return (cm / 2.54) / 12;
  case MILE:
    return (cm / 2.54) / 12 / 5280;
  case CENTIMETER:
    return inch * 2.54;
  case METER:
    return (inch * 2.54) / 100.0;
  case KILOMETER:
    return (inch * 2.54) / 100.0 / 1000;
  default:
    cout << "Invalid Conversion." << endl;
  }
  return 0;
}

double Converter::ConvertWeight(int input_value, WeightUnit input_wt_unit, WeightUnit output_wt_unit) {
  double ounce = 0, gram = 0;
  switch (input_wt_unit) {
  case OUNCE:
    ounce = input_value;
    break;
  case POUND:
    ounce = input_value * 16;
    break;
  case GRAM:
    gram = input_value;
    break;
  case KILOGRAM:
    gram = input_value * 1000;
    break;
  }

  switch (output_wt_unit) {
  case OUNCE:
    return (gram / 28.375);
  case POUND:
    return (gram / 28.375) / 16;
  case GRAM:
    return (ounce * 28.375);
  case KILOGRAM:
    return (ounce * 28.375) / 1000;
  default:
    cout << "Invalid Conversion." << endl;
  }
  return 0;
}

double Converter::ConvertVolume(int input_value, VolumeUnit input_wt_unit, VolumeUnit output_wt_unit) {
  double fluid_ounce = 0, milliliter = 0;
  switch (input_wt_unit) {
  case FLUID_OUNCE:
    fluid_ounce = input_value;
    break;
  case GALLON:
    fluid_ounce = input_value * 128;
    break;
  case MILLILITER:
    milliliter = input_value;
    break;
  case LITER:
    milliliter = input_value * 1000;
    break;
  }

  switch (output_wt_unit) {
  case FLUID_OUNCE:
    return (milliliter / 29.57353);
  case GALLON:
    return (milliliter / 29.57353) / 128;
  case MILLILITER:
    return (fluid_ounce * 29.57353);
  case LITER:
    return (fluid_ounce * 29.57353) / 1000;
  }
  return 0;
}