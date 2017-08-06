#ifndef CONVERTER_H_
#define CONVERTER_H_
enum DistanceUnit { INCH = 1, FOOT, MILE, CENTIMETER, METER, KILOMETER };
enum WeightUnit { OUNCE = 1, POUND, GRAM, KILOGRAM };
enum VolumeUnit { FLUID_OUNCE = 1, GALLON, MILLILITER, LITER };

class Converter {
public:
  double ConvertDistance(int input_value, DistanceUnit input_wt_unit, DistanceUnit output_wt_unit);
  double ConvertWeight(int input_value, WeightUnit input_wt_unit, WeightUnit output_wt_unit);
  double ConvertVolume(int input_value, VolumeUnit input_wt_unit, VolumeUnit output_wt_unit);
};
#endif