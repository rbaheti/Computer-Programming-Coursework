#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>
#include <string.h>

using namespace std;

#define INPUT_FILE "Airports.xml"
static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

class XmlLineParser {
public:
  enum XmlLineType {
    TAG_BEGIN_ONLY = 1,
    COMPLETE_NODE = 2,
    TAG_END_ONLY = 3,
    INVALID_NODE = -1
  };

  bool ParseLine(string line) {
    lineType = FindLineType(line);
    if (lineType == INVALID_NODE) {
      cout << "Invalid node found. It cannot be parsed: " << line;
      return false;
    }

    vector<string> tokens = GetTokens(line);
    if (lineType == TAG_BEGIN_ONLY || lineType == TAG_END_ONLY) {
      tagName = tokens[0];
    }
    else {
      tagName = tokens[0];
      leafValue = tokens[1];
    }
    return true;
  }

  void Reset() {
    lineType = INVALID_NODE;
    tagName.clear();
    leafValue.clear();
  }

  XmlLineType GetLineType() {
    return lineType;
  }

  string GetTagName() {
    return tagName;
  }

  string GetLeafValue() {
    return leafValue;
  }

private:
  static string TrimString(const string& input_string) {
    string output_string = input_string;

    // Trim trailing spaces.
    size_t startpos = output_string.find_first_not_of(" \t");
    if (string::npos == startpos)
    {
      // output_string only contains spaces.
      return "";
    }
    output_string = output_string.substr(startpos);

    // Trim leading spaces.
    size_t endpos = output_string.find_last_not_of(" \t");
    if (string::npos != endpos)
    {
      output_string = output_string.substr(0, endpos + 1);
    }
    return output_string;
  }

  static vector<string> GetTokens(const string& input_string) {
    vector<string> tokens;
    regex pattern("[^<>/]*");
    const sregex_token_iterator end_iter;
    sregex_token_iterator iter(input_string.begin(), input_string.end(), pattern);
    for (; iter != end_iter; ++iter)
    {
      string token = TrimString(*iter);
      if (token.size() > 0) {
        tokens.push_back(*iter);
      }
    }
    return tokens;
  }

  static XmlLineType FindLineType(const string& input_line) {
    regex type1_regex("\\s*<[a-zA-Z]+>");
    regex type2_regex("\\s*<[a-zA-Z]+>[^<]+</[a-zA-Z]+>");
    regex type3_regex("\\s*</[a-zA-Z]+>");
    if (regex_match(input_line, type1_regex)) {
      return TAG_BEGIN_ONLY;
    }
    else if (regex_match(input_line, type2_regex)) {
      return COMPLETE_NODE;
    }
    else if (regex_match(input_line, type3_regex)) {
      return TAG_END_ONLY;
    }
    return INVALID_NODE;
  }

  XmlLineType lineType;
  string tagName;
  string leafValue;
};

class XmlNode {
public:
  ~XmlNode() {
    for (unsigned int i = 0; i < childrenNodes.size(); ++i) {
      delete childrenNodes[i];
    }
    childrenNodes.clear();
  }

  string GetTagName() {
    return tagName;
  }

  void SetTagName(const string& str) {
    tagName = str;
  }

  string GetLeafValue() {
    return leafValue;
  }

  void SetLeafValue(const string& str) {
    leafValue = str;
  }

  void AddChildrenNode(XmlNode* childNode) {
    childrenNodes.push_back(childNode);
  }

  int GetNumChildren() {
    return childrenNodes.size();
  }

  XmlNode* GetChildNode(int i) {
    return childrenNodes[i];
  }

  XmlNode* GetChildNodeByTagName(const string& tagName) {
    for (unsigned int i = 0; i < childrenNodes.size(); ++i) {
      XmlNode* childNode = childrenNodes[i];
      if (childNode->GetTagName() == tagName) {
        return childNode;
      }
    }
    return NULL;
  }

private:
  string tagName;
  string leafValue;
  vector<XmlNode*> childrenNodes;
};

string GetTopNodeCodeTagValue(XmlNode* topNode) {
  XmlNode* locationNode = topNode->GetChildNodeByTagName("Location");
  if (locationNode == NULL) {
    return "";
  }

  XmlNode* codeNode = locationNode->GetChildNodeByTagName("Code");
  if (codeNode == NULL) {
    return "";
  }
  return codeNode->GetLeafValue();
}

bool CompareTopNodesByCodeTag(XmlNode* first, XmlNode* second) {
  string firstCode = GetTopNodeCodeTagValue(first);
  string secondCode = GetTopNodeCodeTagValue(second);
  return firstCode < secondCode;
}

class XmlProcessor {
public:
  ~XmlProcessor() {
    for (unsigned int i = 0; i < topNodesList.size(); ++i) {
      delete topNodesList[i];
    }
    topNodesList.clear();
  }

  void ParseInputFile(const string& filename) {
    stack<string> tagStack;
    vector<queue<XmlNode*>> childrenNodeQueues;

    // Add one queue that will hold the master node (i.e. Airports).
    childrenNodeQueues.push_back(queue<XmlNode*>());

    ifstream inputFile;
    inputFile.open(filename);
    // Error message and exit from code when file doesnot open.
    if (!inputFile) {
      cout << "Error opening file " << filename << "\n";
      exit(1);
    }

    XmlLineParser xmlLineParser;

    char line_array[500];
    while (!inputFile.eof()) {
      inputFile.getline(line_array, 500);
      string line(line_array);

      xmlLineParser.ParseLine(line);

      int linetype = xmlLineParser.GetLineType();
      if (linetype != XmlLineParser::INVALID_NODE) {
        if (linetype == XmlLineParser::TAG_BEGIN_ONLY) {
          // Push the tag on stack.
          tagStack.push(xmlLineParser.GetTagName());
          childrenNodeQueues.push_back(queue<XmlNode*>());
        }
        else if (linetype == XmlLineParser::COMPLETE_NODE) {
          // Construct a leaf node.
          XmlNode* leafNode = new XmlNode();
          leafNode->SetTagName(xmlLineParser.GetTagName());
          leafNode->SetLeafValue(xmlLineParser.GetLeafValue());

          // Add the leaf node to the last queue in childrenNodeQueues.
          // We have to make lastQueue variable a reference else the real queue
          // in childrenNodeQueues will never get modified.
          queue<XmlNode*>& lastQueue = childrenNodeQueues.back();
          lastQueue.push(leafNode);
        }
        else if (linetype == XmlLineParser::TAG_END_ONLY) {
          // Pop the tag from stack.
          string poppedTag = tagStack.top();
          tagStack.pop();

          // Construct the non-leaf node.
          XmlNode* nonLeafNode = new XmlNode();
          nonLeafNode->SetTagName(poppedTag);

          // Get children nodes from the last queue in childrenNodeQueues.
          // And add them as children of nonLeafNode.
          queue<XmlNode*>& childrenQueue = childrenNodeQueues.back();
          const int childrenQueueSize = childrenQueue.size();
          for (int i = 0; i < childrenQueueSize; ++i) {
            nonLeafNode->AddChildrenNode(childrenQueue.front());
            childrenQueue.pop();
          }

          // Delete the last queue which contained children of nonLeafNode.
          childrenNodeQueues.pop_back();

          // nonLeafNode is ready now. Add it to its parent node's queue i.e. 
          // add it to the last queue in childrenNodeQueues.
          queue<XmlNode*>& parentQueue = childrenNodeQueues.back();
          parentQueue.push(nonLeafNode);
        }
      }
      xmlLineParser.Reset();
    }
    if (childrenNodeQueues.size() == 1 && childrenNodeQueues[0].size() == 1) {
      XmlNode* masterNode = childrenNodeQueues[0].front();
      AddTopNodesToList(masterNode);
    }
  }

  void SortTopNodesByCodeTag() {
    std::sort(topNodesList.begin(), topNodesList.end(), CompareTopNodesByCodeTag);
  }

  XmlNode* SearchTopNodesByCodeTag(const string& searchCode)
  {
    int first = 0,
      last = topNodesList.size() - 1,
      middle;

    bool found = false;
    while (!found && first <= last)
    {
      middle = (first + last) / 2;

      string middleCode = GetTopNodeCodeTagValue(topNodesList[middle]);
      if (middleCode == searchCode)
      {
        found = true;
        return topNodesList[middle];
      }
      else if (middleCode > searchCode)
      {
        last = middle - 1;
      }
      else
      {
        first = middle + 1;
      }
    }
    return NULL;
  }

private:
  void AddTopNodesToList(XmlNode* masterNode) {
    for (unsigned int i = 0; i < masterNode->GetNumChildren(); ++i) {
      topNodesList.push_back(masterNode->GetChildNode(i));
    }
  }

  vector<XmlNode*> topNodesList;
};

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
  cout << endl << endl;
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