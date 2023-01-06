// C++ Implementation of Kosaraju's algorithm to print all SCCs
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
  int V;          // No. of vertices
  list<int> *adj; // An array of adjacency lists

  // Fills Stack with vertices (in increasing order of finishing
  // times). The top element of stack has the maximum finishing
  // time
  void fillOrder(int v, bool visited[], stack<int> &Stack);

  // A recursive function to print DFS starting from v
  void DFSUtil(int v, bool visited[]);

  void assignSCCID(int v, bool visited[], int arr[], int w);

public:
  Graph(int V);
  void addEdge(int v, int w);

  // The main function that finds and prints strongly connected
  // components
  void printSCCs();

  // Function that returns reverse (or transpose) of this graph
  Graph getTranspose();

};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}

// A recursive function to print DFS starting from v
void Graph::DFSUtil(int v, bool visited[]) {
  // Mark the current node as visited and print it
  visited[v] = true;
  cout << v << " ";

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      DFSUtil(*i, visited);
}

Graph Graph::getTranspose() {
  Graph g(V);
  for (int v = 0; v < V; v++) {
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i) {
      g.adj[*i].push_back(v);
    }
  }
  return g;
}

void Graph::addEdge(int v, int w) {
  adj[v].push_back(w); // Add w to v’s list.
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) {
  // Mark the current node as visited and print it
  visited[v] = true;

  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      fillOrder(*i, visited, Stack);

  // All vertices reachable from v are processed by now, push v
  Stack.push(v);
}

// This function assigns each vertex its SCC ID by going down
// its SCC and setting each vertex as the least number
void Graph::assignSCCID(int v, bool visited[], int arr[], int w) {
  visited[v] = true;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); i++) {
    if (!visited[*i]) {
      assignSCCID(*i, visited, arr, w);

      // Sets lowest number
      if (*i < w) {
        w = *i;
      }
    }
  }

  // Sets lowest number still
  if (v < w) {
    w = v;
  }

  arr[v] = w;
}

// The main function that finds and prints all strongly connected
// components
void Graph::printSCCs() {
  stack<int> Stack;

  // Mark all the vertices as not visited (For first DFS)
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Fill vertices in stack according to their finishing times
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      fillOrder(i, visited, Stack);

  // Create a reversed graph
  Graph gr = getTranspose();

  // Mark all the vertices as not visited (For second DFS)
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Now process all vertices in order defined by Stack
  while (Stack.empty() == false) {
    // Pop a vertex from stack
    int v = Stack.top();
    Stack.pop();

    // Print Strongly connected component of the popped vertex
    if (visited[v] == false) {
      gr.DFSUtil(v, visited);
      cout << endl;
    }
  }
}

// Driver program to test above functions
int main() {

  int Vert,
  Edges;

  cin >> Vert >> Edges;

  Graph g(Vert);
  for (int eg = 0; eg < Edges; eg++){
    int u, v;
    cin >> u >> v;
    g.addEdge(u,v);
  }

  
  
  g.printSCCs();

  return 0;
}
