#include "../include/graph.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
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

  index_to_url_ = vector<string>(all_nodes_.size(), "");
  for (auto const& x : all_nodes_) {
    url_to_index_[x] = idx;
    index_to_url_[idx] = string(x);
    ++idx;
    if (nodes_.find(x) == nodes_.end()) {
      nodes_[x] = vector<string>(0);
    }
  }
  if (!all_nodes_.empty()) {
    root_ = nodes_.begin()->first;
  }
}

unordered_set<vector<string>> Graph::tarjan() {
  size_t index = 0;
  unordered_map<string, size_t> index_map;
  unordered_map<string, size_t> low_link_map;
  unordered_map<string, bool> on_stack;
//  
  unordered_set<vector<string>> res;
//  
  stack<string> s;
  
  for (const auto& node : all_nodes_) {
    if (index_map.find(node) == index_map.end()) {
      strongConnect(node, index, index_map, low_link_map, on_stack, s, res);
    }
  }
  
  return res;
}

void Graph::strongConnect(const string& node,
                          size_t& index,
                          unordered_map<string, size_t>& index_map,
                          unordered_map<string, size_t>& low_link_map,
                          unordered_map<string, bool>& on_stack,
                          stack<string>& stack,
                          unordered_set<vector<string>>& res) {
  index_map[node] = index;
  low_link_map[node] = index;
  index += 1;
  stack.push(node);
  on_stack[node] = true;
  
  for (const auto& neighbor : nodes_[node]) {
    if (index_map.find(neighbor) == index_map.end()) {
      strongConnect(neighbor, index, index_map, low_link_map, on_stack, stack, res);
      low_link_map[node] = std::min(low_link_map[node], low_link_map[neighbor]);
    } else if (on_stack[neighbor]) {
      low_link_map[node] = std::min(low_link_map[node], index_map[neighbor]);
    }
  }
  
  if (low_link_map[node] == index_map[node]) {
    vector<string> component;
    while (!stack.empty()) {
      const auto& to_check = stack.top();
      stack.pop();
      on_stack[to_check] = false;
      component.push_back(to_check);
      if (to_check != node) {
        res.insert(component);
        component.clear();
      }
    }
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

  while (!s.empty()) {
    string curr = s.top();
    if (visited[url_to_index_[curr]]) {
      s.pop();
      continue;
    }
    to_return.push_back(curr);
    s.pop();
    visited[url_to_index_[curr]] = true;

    for (auto const& n : nodes_[curr]) {
      if (!visited[url_to_index_[n]]) {
        s.push(n);
      }
    }
  }

  return to_return;
}

// 50 iterations should be plenty time to converge
vector<string> Graph::pageRank(const string& start_node) {
  const auto& matrix = genPageRankMatrix(genAdjacency());

  auto cur_vector = vector<double>(matrix.size(), 0.0);
  cur_vector[url_to_index_[start_node]] = 1.0;
  for (size_t i = 0; i < 50; ++i) {
    cur_vector = multMatrixWithVector(matrix, cur_vector);
  }

  vector<string> res(cur_vector.size(), "");

  vector<int> zip_vec(cur_vector.size());
  iota(zip_vec.begin(), zip_vec.end(), 0);
  sort(zip_vec.begin(), zip_vec.end(), [cur_vector](int A, int B) -> bool {
    return cur_vector[A] > cur_vector[B];
  });
  for (size_t i = 0; i < cur_vector.size(); ++i) {
    res[i] = index_to_url_[zip_vec[i]];
  }

  return res;
}

vector<string> Graph::pageRank() { return pageRank(root_); }

const unordered_map<string, vector<string>>& Graph::getNodes() {
  return nodes_;
}

void Graph::printMatrix(vector<vector<double>> m) {
  for (const auto& r : m) {
    cout << "[";
    for (double d : r) {
      cout << d << ", ";
    }
    cout << "]" << endl;
  }
}

vector<vector<double>> Graph::genAdjacency() {
  size_t n = nodes_.size();
  // Creates a 2D vector of size n filled with 0s
  vector<vector<double>> matrix(n, vector<double>(n, 0));

  // Constructs the adjacency matrix
  for (auto const& x : nodes_) {
    auto url = x.first;
    auto connections = x.second;
    int i = url_to_index_[url];
    for (const auto& connection : connections) {
      int j = url_to_index_[connection];
      matrix[j][i] = 1;
    }
  }
  return matrix;
}

vector<vector<double>> Graph::genPageRankMatrix(
    const vector<vector<double>>& m) {
  vector<vector<double>> res = m;
  vector<double> column_sums(m.size(), 0);

  for (const auto& r : m) {
    std::transform(column_sums.begin(), column_sums.end(), r.begin(),
                   column_sums.begin(), std::plus<>());
  }

  for (size_t i = 0; i < m.size(); ++i) {
    if (column_sums[i] < 1) {
      setColumnToValue(res, i, 1.0 / (double)m.size());
    } else {
      divideColumnByValue(res, i, column_sums[i]);
    }
  }

  return res;
}

void Graph::setColumnToValue(vector<vector<double>>& m, size_t col,
                             double val) {
  for (auto& r : m) {
    r[col] = val;
  }
}

void Graph::divideColumnByValue(vector<vector<double>>& m, size_t col,
                                double val) {
  for (auto& r : m) {
    r[col] = r[col] / val;
  }
}

int Graph::getIndexFromUrl(const string& s) { return url_to_index_[s]; }

vector<double> Graph::multMatrixWithVector(const vector<vector<double>>& m,
                                           const vector<double>& v) {
  if (m.size() != v.size()) {
    throw std::invalid_argument(
        "Vector and Matrix dimensions are not compatible");
  }

  vector<double> res(v.size(), 0);

  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = 0; j < v.size(); ++j) {
      res[i] += m[i][j] * v[j];
    }
  }

  return res;
}
