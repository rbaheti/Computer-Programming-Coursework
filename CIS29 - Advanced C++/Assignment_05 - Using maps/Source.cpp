#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <string.h>
#include <assert.h>
#include <map>
using namespace std;

#define INPUT_FREQUENCY_FILE "Frequencies.xml"
#define INPUT_ENCODING_FILE "Speech.txt"

class XmlLineParser {
public:
  enum XmlLineType {
    VALID_NODE = 1,
    INVALID_NODE = -1
  };

  bool ParseLine(string line) {
    if (FindLineType(line) == INVALID_NODE) {
      cout << "Invalid node found. It cannot be parsed: " << line;
      return false;
    }

    vector<string> tokens = GetTokens(line);
    assert(tokens[0].size() == 1);
    tagName = tokens[0].at(0);
    leafValue = atoi(tokens[1].c_str());
    return true;
  }

  void Reset() {
    lineType = INVALID_NODE;
    tagName = '*';
    leafValue = 0;
  }

  XmlLineType GetLineType() {
    return lineType;
  }

  char GetTagName() {
    return tagName;
  }

  int GetLeafValue() {
    return leafValue;
  }

private:
  static string TrimString(const string& input_string) {
    string output_string = input_string;

    // Trim leading spaces.
    size_t startpos = output_string.find_first_not_of(" \t");
    if (string::npos == startpos)
    {
      // output_string only contains spaces.
      return "";
    }
    output_string = output_string.substr(startpos);

    // Trim trailing spaces.
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
      string token = *iter;
      if (token.size() > 0) {
        tokens.push_back(*iter);
      }
    }
    return tokens;
  }

  static XmlLineType FindLineType(const string& input_line) {
    regex regex("<[^>]>[0-9]+<\\\\[^>]>");
    if (regex_match(input_line, regex)) {
      return VALID_NODE;
    }
    return INVALID_NODE;
  }

  XmlLineType lineType;
  char tagName;
  int leafValue;
};

class TreeNode {
public:
  // Constructor to create leaf node.
  TreeNode(char ch, int frequency)
    : character(ch), frequencyCount(frequency), leftChild(NULL), rightChild(NULL) {}

  // Constructor to create non-leaf node.
  TreeNode(int frequency, TreeNode* left, TreeNode* right)
    : character('*'), frequencyCount(frequency), leftChild(left), rightChild(right) {}

  bool IsLeafNode() {
    return character != '*';
  }

  char GetCharacter() const {
    return character;
  }

  int GetFrequencyCount() const {
    return frequencyCount;
  }

  TreeNode* GetLeftChild() const {
    return leftChild;
  }

  TreeNode* GetRightChild() const {
    return rightChild;
  }

private:
  char character; // Only populated for leaf node.
  int frequencyCount;  // Sum of frequencies in the sub-tree.
  TreeNode* leftChild;
  TreeNode* rightChild;
};

class HuffmanTree {
public:
  void ConstructTree(const string& input_file) {
    ifstream inputFile;
    inputFile.open(input_file);
    // Error message and exit from code when file doesnot open.
    if (!inputFile) {
      cout << "Error opening file " << INPUT_FREQUENCY_FILE << "\n";
      cin.get();
      exit(1);
    }

    XmlLineParser xmlLineParser;
    while (!inputFile.eof()) {
      char line_array[50];
      inputFile.getline(line_array, 50);
      xmlLineParser.ParseLine(line_array);

      TreeNode* treeNode = new TreeNode(xmlLineParser.GetTagName(), xmlLineParser.GetLeafValue());
      treeNodes.push_back(treeNode);
      xmlLineParser.Reset();
    }

    // Construct the Huffman tree.
    while (treeNodes.size() > 1) {
      int min_index1, min_index2;
      GetTreeNodesWithMinFrequencies(treeNodes, &min_index1, &min_index2);

      TreeNode* minTreeNode1 = treeNodes[min_index1];
      TreeNode* minTreeNode2 = treeNodes[min_index2];

      // We need to first delete the element with higher index then the element with lower
      // index to correctly delete the 2 elements.
      treeNodes.erase(treeNodes.begin() + std::max(min_index1, min_index2));
      treeNodes.erase(treeNodes.begin() + std::min(min_index1, min_index2));

      TreeNode* newNode = new TreeNode(minTreeNode1->GetFrequencyCount() +
        minTreeNode2->GetFrequencyCount(), minTreeNode1 /* leftChild */,
        minTreeNode2 /* RightChild */);
      treeNodes.push_back(newNode);
    }
    assert(treeNodes.size() == 1);
  }

  TreeNode* GetTreeRoot() {
    return treeNodes[0];
  }

private:
  int treeSize;
  TreeNode* root;
  vector<TreeNode*> treeNodes;

  void GetTreeNodesWithMinFrequencies(const vector<TreeNode*>& treeNodes,
    int* min_index1, int* min_index2) {
    // Vector of treeNodes should have at least 2 nodes.
    assert(treeNodes.size() >= 2);

    // Set min_index1 and min_index2 for the first 2 tree nodes.
    *min_index1 = treeNodes[1]->GetFrequencyCount() > treeNodes[0]->GetFrequencyCount() ? 0 : 1;
    *min_index2 = *min_index1 == 0 ? 1 : 0;
    for (unsigned int i = 2; i < treeNodes.size(); ++i) {
      if (treeNodes[i]->GetFrequencyCount() < treeNodes[*min_index1]->GetFrequencyCount()) {
        *min_index2 = *min_index1;
        *min_index1 = i;
      }
      else if (treeNodes[i]->GetFrequencyCount() < treeNodes[*min_index2]->GetFrequencyCount()) {
        *min_index2 = i;
      }
    }
  }
};

class HuffmanEncoder {
public:
  HuffmanEncoder(TreeNode* rootNode) {
    this->rootNode = rootNode;
  }

  void Encode(map<char, string>* huffman_codes) {
    Encode(rootNode, "", huffman_codes);
  }

private:
  void Encode(TreeNode* treeNode, string parentCode, map<char, string>* huffman_codes) {
    if (treeNode->GetLeftChild() != NULL) {
      if (treeNode->GetLeftChild()->IsLeafNode()) {
        const string code = parentCode + "0";
        huffman_codes->insert(make_pair(treeNode->GetLeftChild()->GetCharacter(), code));
      }
      else {
        Encode(treeNode->GetLeftChild(), parentCode + "0", huffman_codes);
      }
    }

    if (treeNode->GetRightChild() != NULL) {
      if (treeNode->GetRightChild()->IsLeafNode()) {
        const string code = parentCode + "1";
        huffman_codes->insert(make_pair(treeNode->GetRightChild()->GetCharacter(), code));
      }
      else {
        Encode(treeNode->GetRightChild(), parentCode + "1", huffman_codes);
      }
    }
  }

  TreeNode* rootNode;
};

class HuffmanDecoder {
public:
  HuffmanDecoder(TreeNode* rootNode) {
    this->rootNode = rootNode;
  }

  string Decode(string code) {
    string decodedString = "";
    assert(!code.empty());
    int i = 0;
    char character = '*';
    while (i != code.size()) {
      TreeNode* treeNode = rootNode;
      while (!treeNode->IsLeafNode()) {
        if (code.at(i) == '0') {
          treeNode = treeNode->GetLeftChild();
        }
        else {
          assert(code.at(i) == '1');
          treeNode = treeNode->GetRightChild();
        }
        ++i;
      }
      decodedString += treeNode->GetCharacter();
    }
    return decodedString;
  }

private:
  TreeNode* rootNode;
};

class FileIOManipulator {
public: 
  FileIOManipulator(TreeNode* rootNode) {
    this->rootNode = rootNode;
  }

  void PrintEncodedValueToFile() {
    map<char, string> huffman_codes;
    HuffmanEncoder hmEncoder(rootNode);
    hmEncoder.Encode(&huffman_codes);

    ifstream inputFile1;
    inputFile1.open(INPUT_ENCODING_FILE);
    // Error message and exit from code when file doesnot open.
    if (!inputFile1) {
      cout << "Error opening file " << INPUT_ENCODING_FILE << "\n";
      cin.get();
      exit(1);
    }

    char c;
    ofstream outputFile;
    outputFile.open("EncodedFile.txt");
    while (inputFile1.get(c)) {
      auto it = huffman_codes.find(c);
      if (it == huffman_codes.end()) {
        continue;
      }
      outputFile << huffman_codes.find(c)->second;
    }
    outputFile.close();
    inputFile1.close();

    // Note that following line is a shorter version of this:
    // for (map<char, string>::iterator iter = huffman_codes.begin();
    //     iter != huffman_codes.end(); ++iter) {}
    //for (const auto& iter : huffman_codes) {
    //  cout << "Huffman Code for " << iter.first << " is: " << iter.second << endl;
  }

  void PrintDecodedValueToFile() {
    ifstream inEncodedFile;
    inEncodedFile.open("EncodedFile.txt");
    // Error message and exit from code when file doesnot open.
    if (!inEncodedFile) {
      cout << "Error opening file EncodedFile.txt" << "\n";
      cin.get();
      exit(1);
    }

    char ch;
    string line;
    ofstream outputDecodedFile;
    outputDecodedFile.open("DecodedFile.txt");
    while (inEncodedFile.get(ch)) {
      line += ch;
    }
    HuffmanDecoder hmDecoder(rootNode);
    outputDecodedFile << hmDecoder.Decode(line);
    outputDecodedFile.close();
    inEncodedFile.close();
  }

private:
  TreeNode* rootNode;
};

int main() {
  HuffmanTree huffmanTree;
  huffmanTree.ConstructTree(INPUT_FREQUENCY_FILE);
  TreeNode* rootNode = huffmanTree.GetTreeRoot();
  
  FileIOManipulator fileIo(rootNode);
  fileIo.PrintEncodedValueToFile();
  fileIo.PrintDecodedValueToFile();

  cout << "The original file has been encoded and decoded successfully." << endl;

  cin.get();
  cin.get();
  return 0;
}
