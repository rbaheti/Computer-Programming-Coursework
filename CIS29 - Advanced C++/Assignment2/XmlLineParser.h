#ifndef XMLLINEPARSER_H
#define XMLLINEPARSER_H

#include <iostream>
#include <regex>
#include <vector>
#include <string>

using namespace std;

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
#endif