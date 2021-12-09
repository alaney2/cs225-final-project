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

  if (file.is_open()) {
    while (getline(file, line)) {
      vector<string> main_info = split(line, ": ");
      smart_trim(main_info);
      vector<string> neighbors = split(main_info[1], ", ");
      smart_trim(neighbors);

      nodes[main_info[0]] = neighbors;
    }
    file.close();
  } else {
    cout << "Could not open file: " << filename << endl;
  }
}

void Graph::smart_trim(vector<string>& to_trim) {
  for (string& s : to_trim) {
    s.erase(0, s.find_first_not_of(",/\\\t\n\v\f\r "));  // left trim
    s.erase(s.find_last_not_of(",/\\\t\n\v\f\r ") + 1);  // right trim
  }
}

vector<string> Graph::split(const string& to_split, const string& del) {
  vector<string> to_return;

  size_t start = 0;
  size_t end = to_split.find(del);
  while (end != string::npos) {
    to_return.push_back(to_split.substr(start, end - start));
    start = end + del.size();
    end = to_split.find(del, start);
  }
  to_return.push_back(to_split.substr(start, end - start));

  return to_return;
}

string Graph::getRoot() { return root; }
vector<string> Graph::getNeighbor(const string& vertex) {
  return nodes[vertex];
}

void Graph::printInfo() {
  for (auto const& x : nodes) {
    cout << x.first << ": " << x.second.size() << endl;
    for (auto const& y : x.second) {
      cout << "\t" << y << endl;
    }
  }
  cout << "Total Nodes: " << nodes.size() << endl;
}
void Graph::setRoot(const string& new_root) { root = new_root; }

void Graph::dfs() {
  unordered_map<string, bool> visited;
  stack<string> s;
  string longassstring = "";
  for (auto& x : nodes) {
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
    for (auto const& n : nodes[curr]) {
      if (!visited[n]) s.push(n);
    }
  }
  cout << longassstring << endl;
}

void Graph::pageRank() {
  size_t n = nodes.size();
  // Creates a 2D vector of size n filled with 0s
  vector<vector<double>> matrix(n, vector<double>(n, 0));

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
    auto url = x.first;
    auto connections = x.second;
    int i = urlToIndex[url];
    for (const auto& connection : connections) {
      int j = urlToIndex[connection];
      matrix[j][i] = 1;
    }
  }
}
const unordered_map<string, vector<string>>& Graph::getNodes() { return nodes; }
