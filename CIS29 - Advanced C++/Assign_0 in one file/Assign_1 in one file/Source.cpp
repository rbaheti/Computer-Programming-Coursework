#include <iostream>
using namespace std;

enum DistanceUnit { INCH = 1, FOOT, MILE, CENTIMETER, METER, KILOMETER };
enum WeightUnit { OUNCE = 1, POUND, GRAM, KILOGRAM };
enum VolumeUnit { FLUID_OUNCE = 1, GALLON, MILLILITER, LITER };

class Converter {
public:
  double ConvertDistance(int input_value, DistanceUnit input_wt_unit, DistanceUnit output_wt_unit);
  double ConvertWeight(int input_value, WeightUnit input_wt_unit, WeightUnit output_wt_unit);
  double ConvertVolume(int input_value, VolumeUnit input_wt_unit, VolumeUnit output_wt_unit);
};

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

void enableDebug(bool bvalue)
{
  if (!bvalue) return;

  int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

  // Turn on leak-checking bit.
  tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

  // Turn off CRT block checking bit.
  tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;

  // Set flag to the new value.
  _CrtSetDbgFlag(tmpFlag);
}

int main() {
  enableDebug(true);
  Converter converter;
  double value = RequestAction(converter);
  cout << value;

  cin.get();
  cin.get();
  return 0;
}