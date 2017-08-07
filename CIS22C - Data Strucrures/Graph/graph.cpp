#include "graph.h"
#include "queue.h"

Graph::Graph(int vertices) : num_vertices(vertices){
  for (int i = 0; i < num_vertices; ++i) {
    // Add a new int vector to 'adj_matrix'.
    adj_matrix.push_back(vector<int>());

    // Populate the new int vector with 'num_vertices' zeros.
    for (int j = 0; j < num_vertices; ++j) {
      adj_matrix[i].push_back(0);
    }
  }
}

void Graph::AddEdge(int v1_index, int v2_index) {
  adj_matrix[v1_index][v2_index] = 1;
  adj_matrix[v2_index][v1_index] = 1;
}

void Graph::RemoveEdge(int v1_index, int v2_index) {
  adj_matrix[v1_index][v2_index] = 0;
  adj_matrix[v2_index][v1_index] = 0;
}

bool Graph::IsConnected() {
  // reachable_vertices tells which vertices are reachable from vertex 0.
  // visited_vertices tells which vertices have already been visited.
  vector<bool> reachable_vertices, visited_vertices;
  for (int i = 0; i < num_vertices; ++i) {
    reachable_vertices.push_back(false);
    visited_vertices.push_back(false);
  }

  // Traverse the graph through its edges starting from vertex 0.
  Queue<int> vertices_to_visit;
  vertices_to_visit.enqueue(0);

  while (!vertices_to_visit.isEmpty()) {
    int current_vertex;
    vertices_to_visit.dequeue(current_vertex);

    // Check if we already visited the vertex and hence do not need to visit again.
    // This way, we avoid looping through the graph in an infinite loop.
    if (visited_vertices[current_vertex]) {
      continue;
    }

    // Now get all the connections of this vertex and add them to vertices_to_visit.
    // Also, update reachable_vertices.
    for (int j = 0; j < num_vertices; ++j) {
      if (adj_matrix[current_vertex][j] == 1) {
        vertices_to_visit.enqueue(j);
        reachable_vertices[j] = true;
      }
    }
    visited_vertices[current_vertex] = true;
  }

  cout << "Vertices reachable from vertex 0 are:" << endl;
  int num_reachable_vertices = 0;
  for (int i = 0; i < reachable_vertices.size(); ++i) {
    if (reachable_vertices[i]) {
      cout << i << " ";
      ++num_reachable_vertices;
    }
  }
  cout << endl;

  return num_reachable_vertices == num_vertices;
}