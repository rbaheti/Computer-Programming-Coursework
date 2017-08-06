#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <queue>
#include <set>
#include <stack>
#include <algorithm>
#include <string.h>
#include <ctime>

using namespace std;

#define INPUT_FILE "Restaurants.xml"
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

  string GetTagName() const {
    return tagName;
  }

  void SetTagName(const string& str) {
    tagName = str;
  }

  string GetLeafValue() const {
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

  XmlNode* GetChildNodeByTagName(const string& tagName) const {
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

  const vector<XmlNode*> GetTopNodesList() {
    return topNodesList;
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

class Graph {
public:
  Graph(int numVertices) {
    this->numVertices = numVertices;

    for (int i = 0; i < numVertices; ++i) {
      weights.push_back(vector<double>());
      weights.back().resize(numVertices);
    }
  }

  int GetTotalNumVertices() {
    return numVertices;
  }

  void SetWeight(int vertex1, int vertex2, double weight) {
    weights[vertex1][vertex2] = weight;
    weights[vertex2][vertex1] = weight;
  }

  void RunDijkstraForAllNodes(vector<vector<double>>* allDistances,
    vector<vector<int>>* allParentVertices) {
    allDistances->resize(numVertices);
    allParentVertices->resize(numVertices);
    for (int curVertex = 0; curVertex < numVertices; ++curVertex) {
      vector<double>& distances = allDistances->at(curVertex);
      vector<int>& parentVertices = allParentVertices->at(curVertex);

      distances = weights[curVertex];
      parentVertices.resize(numVertices, curVertex);

      set<int> done_vertices;
      done_vertices.insert(curVertex);

      while (done_vertices.size() != numVertices) {
        // Find vertex with minimum distance that is not yet added in done_vertices.
        int minVertex = -1;
        for (int i = 0; i < numVertices; ++i) {
          if (done_vertices.find(i) != done_vertices.end()) continue;

          if (minVertex == -1) {
            minVertex = i;
          }
          else if (distances[i] < distances[minVertex]) {
            minVertex = i;
          }
        }

        done_vertices.insert(minVertex);

        // Adjust distances now;
        for (int i = 0; i < numVertices; ++i) {
          if (done_vertices.find(i) != done_vertices.end()) continue;

          double distanceThroughMinVertex = distances[minVertex] + weights[minVertex][i];
          if (distanceThroughMinVertex < distances[i]) {
            distances[i] = distances[minVertex] + weights[minVertex][i];
            parentVertices[i] = minVertex;
          }
        }
      }
    }
  }


  static string RecursivelyGetShortestPath(vector<int> parentVertices, int source, int destination) {
    if (source == destination) return to_string(source);

    return RecursivelyGetShortestPath(parentVertices, source, parentVertices[destination]) + "->" + to_string(destination);
  }

private:
  int numVertices;
  vector<vector<double>> weights;
};

class Restaurant {
public:
  struct Location {
    string address;
    string city;
    string state;
    string phone;
    double latitude;
    double longitude;
  };

  void AddLocation(const Location& location) {
    locations.push_back(location);
  }

  Graph CreateLocationGraph() {
    Graph graph(locations.size());
    for (int i = 0; i < locations.size(); ++i) {
      for (int j = i + 1; j < locations.size(); ++j) {
        double distance = DistanceInKiloMeters(
          locations[i].latitude, locations[i].longitude,
          locations[j].latitude, locations[j].longitude);;
        graph.SetWeight(i, j, distance);
      }
    }
    return graph;
  }

  void PrintRestaurantAddress(int index) {
    cout << locations[index].address << ", " << locations[index].city
      << ", " << locations[index].state;
  }

private:
  vector<Location> locations;
};

class HamiltonianAlgorithm {
public:
  HamiltonianAlgorithm(Graph* graph, vector<vector<double>>& allDistances) {
    this->graph = graph;
    totalNumVertices = graph->GetTotalNumVertices();
    this->allDistances = allDistances;
  }

  void PrintHamiltonianPaths() {
    BreakUpGraph();

    cout << endl;
    cout << "Broke the original graph into following smaller sized Hamiltonian paths:" << endl;
    for (const auto& vertexGroup : vertexGroups) {
      hamiltonianPathDistances.push_back(0);
      hamiltonianPaths.push_back(vector<int>());
      double& minSum = hamiltonianPathDistances.back();
      vector<int>& minPathVertices = hamiltonianPaths.back();
      RecursivelyGetHamiltonialPath(allDistances, vertexGroup, vector<int>(),
        &minSum, &minPathVertices);
      borderVertexGroup.push_back(minPathVertices[0]);
      borderVertexGroup.push_back(minPathVertices.back());

      cout << "Hamiltonian path with distance " << minSum << "km: ";
      for (int i = 0; i < minPathVertices.size(); ++i) {
        cout << minPathVertices[i] << (i < (minPathVertices.size() - 1) ? "->" : "");
      }
      cout << endl;
    }
    vertexGroups = hamiltonianPaths;
  }

  void PrintHamiltonianCircuit() {
    double minSum = 0;
    vector<int> minBorderPathVertices;
    RecursivelyGetHamiltonialCircuit(allDistances, borderVertexGroup, vector<int>(),
      &minSum, &minBorderPathVertices);
    for (double pathDistance : hamiltonianPathDistances) {
      minSum += pathDistance;
    }

    cout << endl << "Following Hamiltonian Circuit connects above Hamiltonian paths with smallest distance "
      << minSum << "km:" << endl;
    for (int i = 0; i < minBorderPathVertices.size(); i += 2) {
      int firstEndVertex = minBorderPathVertices[i];
      int secondEndVertex = minBorderPathVertices[i + 1];

      int vertexGroupIndex = 0;
      for (vertexGroupIndex = 0; vertexGroupIndex < vertexGroups.size(); ++vertexGroupIndex) {
        auto& vertexGroup = vertexGroups[vertexGroupIndex];
        if (vertexGroup[0] == firstEndVertex || vertexGroup.back() == firstEndVertex) {
          break;
        }
      }

      auto& vertexGroup = vertexGroups[vertexGroupIndex];
      int direction = vertexGroup[0] == firstEndVertex ? 1 : -1;
      int j = vertexGroup[0] == firstEndVertex ? 0 : (vertexGroup.size() - 1);
      int numVerticesPrinted = 0;
      while (numVerticesPrinted != vertexGroup.size()) {
        cout << vertexGroup[j] << "->";
        j += direction;
        ++numVerticesPrinted;
      }
    }
    cout << minBorderPathVertices[0];
    cout << endl;
  }

private:
  void BreakUpGraph() {
    set<int> notDoneVertices;
    for (int i = 0; i < totalNumVertices; ++i) {
      notDoneVertices.insert(i);
    }

    while (!notDoneVertices.empty()) {
      int notDoneVertex = *notDoneVertices.begin();

      set<int> closestVertices;
      closestVertices.insert(notDoneVertex);
      notDoneVertices.erase(notDoneVertex);

      // Find 1 closest vertex of notDoneVertex.
      if (!notDoneVertices.empty()) {
        int closestVertex = *notDoneVertices.begin();
        double closestVertexDistance = allDistances[notDoneVertex][closestVertex];
        for (int j : notDoneVertices) {
          if (allDistances[notDoneVertex][j] < closestVertexDistance) {
            closestVertex = j;
            closestVertexDistance = allDistances[notDoneVertex][j];
          }
        }

        closestVertices.insert(closestVertex);
        notDoneVertices.erase(closestVertex);
      }

      // Iterate over notDoneVertices to find vertices which are closer to closestVertices
      // than any of notDoneVertices vertices.
      bool updatedClosestVertices = false;
      do {
        updatedClosestVertices = false;
        for (int i = 0; i < totalNumVertices; ++i) {
          if (notDoneVertices.find(i) == notDoneVertices.end()) continue;

          int closestVertex = -1;
          double closestVertexDistance = -1;
          for (int j = 0; j < totalNumVertices; ++j) {
            if (i == j) continue;

            if (closestVertex == -1 ||
              allDistances[i][j] < closestVertexDistance) {
              closestVertex = j;
              closestVertexDistance = allDistances[i][j];
            }
          }

          if (closestVertices.find(closestVertex) != closestVertices.end()) {
            updatedClosestVertices = true;
            closestVertices.insert(i);
            notDoneVertices.erase(i);
          }
        }
      } while (updatedClosestVertices);
      vertexGroups.push_back(vector<int>(closestVertices.begin(), closestVertices.end()));
    }
  }


  void RecursivelyGetHamiltonialPath(const vector<vector<double>>& allDistances,
    const vector<int>& remainingVertices,
    const vector<int>& currentPathVertices,
    double* minSum, vector<int>* minPathVertices) {
    if (remainingVertices.size() == 1) {
      vector<int> updatedCurrentPathVertices = currentPathVertices;
      updatedCurrentPathVertices.push_back(remainingVertices[0]);

      double currentSum = 0;
      int source = updatedCurrentPathVertices[0];
      for (int i = 1; i < updatedCurrentPathVertices.size(); ++i) {
        int destination = updatedCurrentPathVertices[i];
        currentSum += allDistances[source][destination];
        source = destination;
      }

      if (minPathVertices->empty() || currentSum < *minSum) {
        *minSum = currentSum;
        *minPathVertices = updatedCurrentPathVertices;
      }
      return;
    }

    for (int i = 0; i < remainingVertices.size(); ++i) {
      vector<int> updatedRemainingVertices = remainingVertices;
      updatedRemainingVertices.erase(updatedRemainingVertices.begin() + i);
      vector<int> updatedCurrentPathVertices = currentPathVertices;
      updatedCurrentPathVertices.push_back(remainingVertices[i]);
      RecursivelyGetHamiltonialPath(allDistances, updatedRemainingVertices, updatedCurrentPathVertices,
        minSum, minPathVertices);
    }
  }

  void RecursivelyGetHamiltonialCircuit(const vector<vector<double>>& allDistances,
    const vector<int>& remainingVertices,
    const vector<int>& currentPathVertices,
    double* minSum, vector<int>* minPathVertices) {
    if (remainingVertices.size() == 2) {
      for (int direction = 0; direction < 2; ++direction) {
        vector<int> updatedCurrentPathVertices = currentPathVertices;
        updatedCurrentPathVertices.push_back(remainingVertices[direction]);
        updatedCurrentPathVertices.push_back(remainingVertices[(direction + 1) % 2]);

        int firstVertex = updatedCurrentPathVertices[0];
        int lastVertex = updatedCurrentPathVertices.back();

        double currentSum = allDistances[lastVertex][firstVertex];
        int source = updatedCurrentPathVertices[1];
        for (int i = 2; i < updatedCurrentPathVertices.size(); i += 2) {
          int destination = updatedCurrentPathVertices[i];
          currentSum += allDistances[source][destination];
          source = updatedCurrentPathVertices[i + 1];
        }

        if (minPathVertices->empty() || currentSum < *minSum) {
          *minSum = currentSum;
          *minPathVertices = updatedCurrentPathVertices;
        }
      }
      return;
    }

    for (int i = 0; i < remainingVertices.size(); i += 2) {
      int firstEndVertex = remainingVertices[i];
      int secondEndVertex = remainingVertices[i + 1];

      vector<int> updatedRemainingVertices = remainingVertices;
      updatedRemainingVertices.erase(updatedRemainingVertices.begin() + i);
      updatedRemainingVertices.erase(updatedRemainingVertices.begin() + i);

      {
        vector<int> updatedCurrentPathVertices = currentPathVertices;
        updatedCurrentPathVertices.push_back(firstEndVertex);
        updatedCurrentPathVertices.push_back(secondEndVertex);
        RecursivelyGetHamiltonialCircuit(allDistances, updatedRemainingVertices, updatedCurrentPathVertices,
          minSum, minPathVertices);
      }
      {
        vector<int> updatedCurrentPathVertices = currentPathVertices;
        updatedCurrentPathVertices.push_back(secondEndVertex);
        updatedCurrentPathVertices.push_back(firstEndVertex);
        RecursivelyGetHamiltonialCircuit(allDistances, updatedRemainingVertices, updatedCurrentPathVertices,
          minSum, minPathVertices);
      }
    }
  }
  
  Graph* graph;
  int totalNumVertices;
  vector<vector<double>> allDistances;
  vector<vector<int>> vertexGroups;
  vector<vector<int>> hamiltonianPaths;
  vector<double> hamiltonianPathDistances;
  vector<int> borderVertexGroup;
};

int main() {
  XmlProcessor xmlProcessor;
  xmlProcessor.ParseInputFile(INPUT_FILE);

  Restaurant restaurant;
  for (const XmlNode* locationNode : xmlProcessor.GetTopNodesList()) {
    const XmlNode* addressNode = locationNode->GetChildNodeByTagName("Address");
    const XmlNode* cityNode = locationNode->GetChildNodeByTagName("City");
    const XmlNode* stateNode = locationNode->GetChildNodeByTagName("State");
    const XmlNode* phoneNode = locationNode->GetChildNodeByTagName("Phone");
    const XmlNode* latitudeNode = locationNode->GetChildNodeByTagName("Latitude");
    const XmlNode* longitudeNode = locationNode->GetChildNodeByTagName("Longitude");

    Restaurant::Location location;
    location.address = addressNode->GetLeafValue();
    location.city = cityNode->GetLeafValue();
    location.state = stateNode->GetLeafValue();
    location.phone = phoneNode->GetLeafValue();
    location.latitude = stod(latitudeNode->GetLeafValue());
    location.longitude = stod(longitudeNode->GetLeafValue());
    restaurant.AddLocation(location);
  }

  Graph graph = restaurant.CreateLocationGraph();
  const int totalNumVertices = graph.GetTotalNumVertices();

  cout << endl << endl << "List of all restaurants:" << endl;
  for (int i = 0; i < totalNumVertices; ++i) {
    cout << "Restaurant " << i << ": ";
    restaurant.PrintRestaurantAddress(i);
    cout << endl;
  }

  // Run Dijkstra's algorithm on the graph to find all pairs shortest paths.
  const clock_t dijkstra_begin_time = clock();
  vector<vector<double>> allDistances;
  vector<vector<int>> allParentVertices;
  graph.RunDijkstraForAllNodes(&allDistances, &allParentVertices);
  const clock_t dijkstra_end_time = clock();
  
  cout << endl << "Output of Dijkstra's algorithm:" << endl;
  for (int i = 0; i < totalNumVertices; ++i) {
    for (int j = 0; j < totalNumVertices; ++j) {
      if (i == j) continue;

      cout << "Shortest path between Restaurant " << i << " and Restaurant " << j
        << " is " << graph.RecursivelyGetShortestPath(allParentVertices[i], i, j)
        << ". Total Distance: " << allDistances[i][j] << "km" << endl;
    }
  }

  cout << endl << "It took " << float(dijkstra_end_time - dijkstra_begin_time) / CLOCKS_PER_SEC
    << " seconds to run Dijkstra's algoritm to find all pairs shortest path." << endl;
  
  const clock_t hamiltonian_begin_time = clock();
  HamiltonianAlgorithm hamiltonian(&graph, allDistances);
  hamiltonian.PrintHamiltonianPaths();
  hamiltonian.PrintHamiltonianCircuit();
  const clock_t hamiltonian_end_time = clock();
  
  cout << endl << "It took " << float(hamiltonian_end_time - hamiltonian_begin_time) / CLOCKS_PER_SEC
    << " seconds to run Hamiltonian Circuit algoritm to find shortest circuit." << endl;
  
  cin.get();
  cin.get();
  return 0;
}