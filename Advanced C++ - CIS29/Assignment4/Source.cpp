#include <bitset>
#include <iostream>
#include <fstream>
#include <thread>   
#include <mutex>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include <condition_variable>
#include <chrono>
#include <regex>
using namespace std;
#define INPUT_FILE "Robot.xml"

class XmlLineParser {
public:
  enum XmlLineType {
    TAG_BEGIN_ONLY = 1,
    COMPLETE_NODE = 2,
    TAG_END_ONLY = 3,
    INVALID_NODE = -1
  };

  bool ParseLine(string line, int lineNo) {
    lineType = FindLineType(line);
    if (lineType == INVALID_NODE) {
      cout << "Invalid node found on line#" << lineNo << ". It cannot be parsed: " << line;
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
    regex type1_regex("\\s*<[a-zA-Z0-9]+>");
    regex type2_regex("\\s*<[a-zA-Z0-9]+>[^<]+<\\\\[a-zA-Z0-9]+>");
    regex type3_regex("\\s*<\\\\[a-zA-Z0-9]+>");
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

  int GetNumChildren() const {
    return childrenNodes.size();
  }

  XmlNode* GetChildNode(int i) const {
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

  vector<XmlNode*> GetTopNodesList() {
    return topNodesList;
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
    int lineNo = 1;
    while (!inputFile.eof()) {
      inputFile.getline(line_array, 500);
      string line(line_array);

      xmlLineParser.ParseLine(line, lineNo++);

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

private:
  void AddTopNodesToList(XmlNode* masterNode) {
    for (unsigned int i = 0; i < masterNode->GetNumChildren(); ++i) {
      topNodesList.push_back(masterNode->GetChildNode(i));
    }
  }

  vector<XmlNode*> topNodesList;
};

class Command {
public:
  enum Arm {
    ARM1 = 1,
    ARM2 = 2,
    ARM3 = 3,
    ARM4 = 4
  };

  enum MotionDirection {
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4,
    CLOCKWISE = 5,
    COUNTER_CLOCKWISE = 6
  };

  enum Speed {
    FAST = 1,
    SLOW = 2
  };

  Command(Arm armIn, MotionDirection motionDirectionIn, Speed speedIn, unsigned int degreesOfRotationIn)
    : arm(armIn), motionDirection(motionDirectionIn), speed(speedIn), degreesOfRotation(degreesOfRotationIn) {}

  Arm GetArm() const {
    return arm;
  }

  string GetArmStr() const {
    switch (arm) {
    case ARM1: return "Arm1";
    case ARM2: return "Arm2";
    case ARM3: return "Arm3";
    case ARM4: return "Arm4";
    }
    return "";
  }

  MotionDirection GetMotionDirection() const {
    return motionDirection;
  }

  string GetMotionDirectionStr() const {
    switch (motionDirection) {
    case LEFT: return "Left";
    case RIGHT: return "Right";
    case UP: return "Up";
    case DOWN: return "Down";
    case CLOCKWISE: return "Clockwise";
    case COUNTER_CLOCKWISE: return "Counter-clockwise";
    }
    return "";
  }

  Speed GetSpeed() const {
    return speed;
  }

  string GetSpeedStr() const {
    switch (speed) {
    case FAST: return "Fast";
    case SLOW: return "Slow";
    }
    return "";
  }

  unsigned int GetDegreesOfRotation() const {
    return degreesOfRotation;
  }

private:
  Arm arm;
  MotionDirection motionDirection;
  Speed speed;
  unsigned int degreesOfRotation;
};

class CommandExtractor {
public:
  CommandExtractor() {
    XmlProcessor xmlProcessor;
    xmlProcessor.ParseInputFile(INPUT_FILE);

    for (const XmlNode* motionNode : xmlProcessor.GetTopNodesList()) {
      assert(motionNode->GetNumChildren() == 1);
      XmlNode* armNode = motionNode->GetChildNode(0);
      string armStr = armNode->GetTagName();

      assert(armNode->GetNumChildren() == 1);
      XmlNode* commandNode = armNode->GetChildNode(0);

      string commandStr = commandNode->GetLeafValue();
      assert(commandStr.size() == 2);

      char byte1 = commandStr.at(0);
      char byte2 = commandStr.at(1);

      Command::Arm arm = Command::ARM1;
      if (armStr == "Arm1") {
        arm = Command::ARM1;
      }
      else if (armStr == "Arm2") {
        arm = Command::ARM2;
      }
      else if (armStr == "Arm3") {
        arm = Command::ARM3;
      }
      else if (armStr == "Arm4") {
        arm = Command::ARM4;
      }

      // Find Arm from the least significant 6 bits in byte1.
      Command::MotionDirection motionDirection = Command::LEFT;
      if (byte1 & 0x01) {
        motionDirection = Command::LEFT;
      }
      else if (byte1 & 0x02) {
        motionDirection = Command::RIGHT;
      }
      else if (byte1 & 0x04) {
        motionDirection = Command::UP;
      }
      else if (byte1 & 0x08) {
        motionDirection = Command::DOWN;
      }
      else if (byte1 & 0x10) {
        motionDirection = Command::CLOCKWISE;
      }
      else if (byte1 & 0x20) {
        motionDirection = Command::COUNTER_CLOCKWISE;
      }

      // Find Speed from the most significant 2 bits in byte1.
      Command::Speed speed = Command::FAST;
      if (byte1 & 0x40) {
        speed = Command::FAST;
      }
      else if (byte1 & 0x80) {
        speed = Command::SLOW;
      }

      // Find degrees of rotation from the second byte.
      unsigned int degreesOfRotation = static_cast<unsigned char>(byte2);

      Command command(arm, motionDirection, speed, degreesOfRotation);
      commandList.push_back(command);
    }
  }

  const vector<Command>& GetCommandList() {
    return commandList;
  }

private:
  vector<Command> commandList;
};

class Robot {
private:
  // Needed to create thread object.
  void ExecuteCommandOnThread(const Command& command) {
    cout << command.GetSpeedStr() << " " << command.GetMotionDirectionStr() << " "
      << command.GetDegreesOfRotation() << " degrees\n";
    unsigned int msec;
    if (command.GetSpeed() == Command::FAST) {
      msec = command.GetDegreesOfRotation() * 1;
    }
    else if (command.GetSpeed() == Command::SLOW) {
      msec = command.GetDegreesOfRotation() * 2;
    }

    this_thread::sleep_for(chrono::milliseconds(msec));
  }

public:
  void ExecuteCommand(const Command& command) {
    mu.lock();
    thread commandExecutor(&Robot::ExecuteCommandOnThread, this, command);
    if (commandExecutor.joinable()) {
      commandExecutor.join();
    }
    mu.unlock();
  }

private:
  mutex mu;
};

class CommandProcessor {
public:
  CommandProcessor(Robot* robotIn) : robot(robotIn) {}

  void AddCommand(const Command& command) {
    commandList.push_back(command);
  }

  void Start() {
    commandProcessorThread = thread(&CommandProcessor::CommandProcessorLoop, this);
  }

  void Join() {
    if (commandProcessorThread.joinable()) {
      commandProcessorThread.join();
    }
  }

  void CommandProcessorLoop() {
    for (const Command& command : commandList) {
      robot->ExecuteCommand(command);
    }
  }

private:
  Robot* robot;
  vector<Command> commandList;
  thread commandProcessorThread;
};

class RobotOperator {
public:
  RobotOperator(Robot* robot) {
    this->robot = robot;
  }

  CommandExtractor commandExtractor;

  void RobotOperator::Start() {
    vector<CommandProcessor> commandProcessors;
    for (int i = 0; i < 4; ++i) {
      commandProcessors.push_back(CommandProcessor(robot));
    }

    for (const Command& command : commandExtractor.GetCommandList()) {
      commandProcessors[command.GetArm() - 1].AddCommand(command);
    }

    for (int i = 0; i < 4; ++i) {
      commandProcessors[i].Start();
    }

    for (int i = 0; i < 4; ++i) {
      commandProcessors[i].Join();
    }
  }

private:
  Robot* robot;
};

void main()
{
  Robot robot;
  RobotOperator robotOperator(&robot);
  robotOperator.Start();

  cin.get();
  cin.get();
}