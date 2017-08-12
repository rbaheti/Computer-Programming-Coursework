#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include "XmlLineParser.h"
#include "XmlNode.h"
#include "XmlProcessor.h"

using namespace std;

#define INPUT_FILE "Airports.xml"
static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

double DistanceInKiloMeters(const double fromLat, const double fromLon,
  const double toLat, const double toLon) {
  double latitudeArc = (fromLat - toLat) * DEG_TO_RAD;
  double longitudeArc = (fromLon - toLon) * DEG_TO_RAD;
  double latitudeH = sin(latitudeArc * 0.5);
  latitudeH *= latitudeH;
  double lontitudeH = sin(longitudeArc * 0.5);
  lontitudeH *= lontitudeH;
  double tmp = cos(fromLat*DEG_TO_RAD) * cos(toLat*DEG_TO_RAD);
  return EARTH_RADIUS_IN_METERS * 2.0 * asin(sqrt(latitudeH + tmp*lontitudeH)) / 1000;
}

string toUpperCase(string input) {
  char* charInput = new char[input.size() + 1];
  strcpy(charInput, input.c_str());

  char* orig_charInput = charInput;

  while (*charInput != '\0') {
    *charInput = toupper(*charInput);
    charInput++;
  }
  return string(orig_charInput, input.size());
}

int main() {
  XmlProcessor xmlProcessor;
  xmlProcessor.ParseInputFile(INPUT_FILE);
  
  xmlProcessor.SortTopNodesByCodeTag();
  
  string fromCode, toCode;
  cout << "Enter code of first Airport: ";
  cin >> fromCode;
  fromCode = toUpperCase(fromCode);
  cout << "Enter code of second Airport: ";
  cin >> toCode;
  toCode = toUpperCase(toCode);
  
  XmlNode* fromAirportNode = xmlProcessor.SearchTopNodesByCodeTag(fromCode);
  XmlNode* toAirportNode = xmlProcessor.SearchTopNodesByCodeTag(toCode);
  
  XmlNode* fromCoordinatesNode = fromAirportNode->GetChildNodeByTagName("Coordinates");
  XmlNode* toCoordinatesNode = toAirportNode->GetChildNodeByTagName("Coordinates");
  
  XmlNode* fromLatitudeNode = fromCoordinatesNode->GetChildNodeByTagName("Latitude");
  XmlNode* fromLongitudeNode = fromCoordinatesNode->GetChildNodeByTagName("Longitude");
  
  XmlNode* toLatitudeNode = toCoordinatesNode->GetChildNodeByTagName("Latitude");
  XmlNode* toLongitudeNode = toCoordinatesNode->GetChildNodeByTagName("Longitude");
  
  double distance = DistanceInKiloMeters(
    stod(fromLatitudeNode->GetLeafValue()), stod(fromLongitudeNode->GetLeafValue()),
    stod(toLatitudeNode->GetLeafValue()), stod(toLongitudeNode->GetLeafValue()));
    cout << "Distance between " << fromCode << " and " << toCode << " Airports is: "
      << distance << " km";

  cin.get();
  cin.get();
  return 0;
}