#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Graph {
public:
  Graph(int vertices);

  void AddEdge(int v1_index, int v2_index);

  void RemoveEdge(int v1_index, int v2_index);

  bool IsConnected();

private:
  const int num_vertices;
  vector<vector<int>> adj_matrix;
};