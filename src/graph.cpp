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
          if(url.back() == '/')
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
          if(url.back() == '/')
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


void Graph::dfs() {
  unordered_map<string, bool> visited;
  stack<string> s;
  string longassstring = "";
  for (auto &x : nodes) {
    visited[x.first] = false;
  }
  s.push(root);
  visited[root] = true;
  while (!s.empty()) {
    string curr = s.top();
    s.pop();
    visited[curr] = true;
    longassstring += curr;
    longassstring += '\n';
    for (auto const &n : nodes[curr]) {
      if(!visited[n]) s.push(n);
    }
  }
  cout << longassstring << endl;
}

void Graph::pageRank() {
  int n = nodes.size();
  // Creates a 2D vector of size n filled with 0s
  vector<vector<double>> matrix(n, vector<double> (n, 0));

  unordered_map<string, int> urlToIndex;
  int idx = 0;
  // C++11+
  for (auto const& x : nodes) {
    string url = x.first;
    urlToIndex[url] = idx;
    ++idx;
  }
  // Constructs the adjacency matrix
  for (auto const& x : nodes) {
    string url = x.first;
    string connections = x.second;
    int i = urlToIndex[url];
    for (string connection : connections) {
      int j = urlToIndex[connection];
      matrix[j][i] = 1;
    }
  }
}