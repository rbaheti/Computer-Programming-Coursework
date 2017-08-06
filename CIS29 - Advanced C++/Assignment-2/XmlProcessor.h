#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <algorithm>
#include "XmlLineParser.h"
#include "XmlNode.h"

using namespace std;

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