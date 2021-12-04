#include "../include/graph.h"

#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;

Graph::Graph(const string& filename) { addFileInfoToGraph(filename); }

Graph::Graph(const vector<string>& filenames) {
  for (const string& filename : filenames) {
    addFileInfoToGraph(filename);
  }
}

void Graph::addFileInfoToGraph(const string& filename) {
  string line;
  ifstream file(filename);
  string url = "";
  bool flag = true;
  if (file.is_open()) {
    while (getline(file, line)) {
      int counter = 1;

      string vertex = "";
      vector<string> neighbors;
      neighbors.clear();
      for (char& c : line) {
        if (c == ' ' && counter == 1) {  // vertex url
          url.pop_back();
          vertex = url;
          nodes[vertex] = neighbors;
          url = "";
          counter--;
          if (flag) {
            root = vertex;
            flag = false;
          }
        } else if (c == ' ') {  // neighbors url
          url.pop_back();
          nodes[vertex].push_back(url);
          url = "";
        } else {
          url += c;
        }
      }
    }
    file.close();
  } else {
    cout << "Could not open file: " << filename << endl;
  }
}

string Graph::getRoot() { return root; }
vector<string> Graph::getNeighbor(const string& vertex) {
  return nodes[vertex];
}

void Graph::printInfo() {
  for (auto const& x : nodes) {
    cout << x.first << ": " << x.second.size() << endl;
  }
  cout << "Total Nodes: " << nodes.size() << endl;
}
void Graph::setRoot(const string& new_root) { root = new_root; }
