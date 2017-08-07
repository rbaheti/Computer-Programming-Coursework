#include <iostream>
#include <cstdlib>   // needed for the exit() function
#include <fstream>
#include <string>
#include <vector>
#include "graph.h"

int main() {
  int num_vertices;
  cout << "Enter number of vertices: ";
  cin >> num_vertices;

  int num_edges;
  cout << "Enter number of edges: ";
  cin >> num_edges;

  Graph graph(num_vertices);
  for (int i = 0; i < num_edges; ++i) {
    cout << "Enter the 2 vertices of edge#" << i + 1 << ": ";
    int v1, v2;
    cin >> v1;
    cin >> v2;
    graph.AddEdge(v1, v2);
  }

  cout << "The graph is" << (graph.IsConnected() ? "" : " not") << " connected.";
  cin.get();
  cin.get();
  return 0;
}