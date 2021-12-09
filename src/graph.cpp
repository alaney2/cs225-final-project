#include "../include/graph.h"

#include <fstream>
#include <iostream>
#include <unordered_set>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::unordered_set;

Graph::Graph(const string& filename) : Graph(vector<string>{filename}) {}

Graph::Graph(const vector<string>& filenames) {
  for (const string& filename : filenames) {
    addFileInfoToGraph(filename);
  }
  int idx = 0;
  for (auto const& x : all_nodes_) {
    urlToIndex_[x] = idx;
    ++idx;
    if (nodes_.find(x) == nodes_.end()) {
      nodes_[x] = vector<string>(0);
    }
  }
  if (!all_nodes_.empty()) {
    root_ = nodes_.begin()->first;
  }
}

void Graph::addFileInfoToGraph(const string& filename) {
  string line;
  ifstream file(filename);

  if (file.is_open()) {
    while (getline(file, line)) {
      vector<string> main_info = split(line, ": ");
      smartTrim(main_info);
      vector<string> neighbors = split(main_info[1], ", ");
      smartTrim(neighbors);
      
      all_nodes_.insert(main_info[0]);
      for (const auto& s : neighbors) {
        all_nodes_.insert(s);
      }
      nodes_[main_info[0]] = neighbors;
    }
    file.close();
  } else {
    cout << "Could not open file: " << filename << endl;
  }
}

void Graph::smartTrim(vector<string>& to_trim) {
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

string Graph::getRoot() { return root_; }
vector<string> Graph::getNeighbor(const string& vertex) {
  return nodes_[vertex];
}

void Graph::printInfo() {
  for (auto const& x : nodes_) {
    cout << x.first << ": " << x.second.size() << endl;
    for (auto const& y : x.second) {
      cout << "\t" << y << endl;
    }
  }
  cout << "Total Nodes_: " << nodes_.size() << endl;
}
void Graph::setRoot(const string& new_root_) { root_ = new_root_; }

vector<string> Graph::dfs() {
  vector<bool> visited(all_nodes_.size(), false);

  stack<string> s;
  s.push(root_);

  vector<string> to_return;
  visited[urlToIndex_[root_]] = true;

  while (!s.empty()) {
    string curr = s.top();
    to_return.push_back(curr);
    s.pop();
    visited[urlToIndex_[curr]] = true;

    for (auto const& n : nodes_[curr]) {
      if (!visited[urlToIndex_[n]]) {
        s.push(n);
      }
    }
  }
  
  return to_return;
}

void Graph::pageRank() {
  size_t n = nodes_.size();
  // Creates a 2D vector of size n filled with 0s
  vector<vector<double>> matrix(n, vector<double>(n, 0));

  // Constructs the adjacency matrix
  for (auto const& x : nodes_) {
    auto url = x.first;
    auto connections = x.second;
    int i = urlToIndex_[url];
    for (const auto& connection : connections) {
      int j = urlToIndex_[connection];
      matrix[j][i] = 1;
    }
  }
}

const unordered_map<string, vector<string>>& Graph::getNodes() {
  return nodes_;
}
