#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <vector>
using namespace std;

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
#endif