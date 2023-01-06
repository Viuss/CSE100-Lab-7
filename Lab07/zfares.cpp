//Collaborated with Andre Limos and Andrew Mouilleseaux
//Utilized code from geeksforgeeks.org
#include <iostream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
  int V;
  list<int> *adj;

  void fillOrder(int v, bool checked[], stack<int> &Stack);
  // Depth first search print recursively
  //Replaced the DFSUtil function
  void assignSCCID(int v, bool checked[], int arr[], int w);

public:
  Graph(int V);
  void addEdge(int v, int w);
  // Find and print components if strongly connected
  void printSCCs();
  // Reverse graph getter
  Graph getTranspose();
};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}

Graph Graph::getTranspose() {
  Graph g(V);
  for (int v = 0; v < V; v++) {
    // Iterate for all adjacent
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

void Graph::fillOrder(int v, bool checked[], stack<int> &Stack) {
  // Mark as checked then print
  checked[v] = true;
  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!checked[*i])
      fillOrder(*i, checked, Stack);
  // After all have been seen, push
  Stack.push(v);
}

// Assign vertex SCC ID, setting each SCC to least 
void Graph::assignSCCID(int v, bool checked[], int arr[], int w) {
  checked[v] = true;

  list<int>::iterator i;
  for (i = adj[v].begin(); i != adj[v].end(); i++) {
    if (!checked[*i]) {
      assignSCCID(*i, checked, arr, w);
      // Sets lowest either way
      if (*i < w) {
        w = *i;
      }
    }
  }
  // Sets lowest either way
  if (v < w) {
    w = v;
  }
  arr[v] = w;
}


void Graph::printSCCs() {
  stack<int> Stack;
  int arr[V];

  // Uncheck all
  bool *checked = new bool[V];
  for (int i = 0; i < V; i++)
    checked[i] = false;

  for (int i = 0; i < V; i++)
    if (checked[i] == false)
      fillOrder(i, checked, Stack);

  Graph gr = getTranspose();

  // Uncheck all again
  for (int i = 0; i < V; i++)
    checked[i] = false;

  while (Stack.empty() == false) {
    int v = Stack.top();
    Stack.pop();

    int w = v;
    if (checked[v] == false) {
      gr.assignSCCID(v,checked, arr, w);
    }
  }
  for(int i=0;i<V;i++){
      cout<<arr[i]<<endl;
  }
}


int main() {

  int Vert, Edges;

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