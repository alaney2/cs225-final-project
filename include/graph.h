//
// Created by becla on 12/4/2021.
//
#pragma once

#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::stack;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

class Graph {
 public:
  explicit Graph(const string& filename);
  explicit Graph(const vector<string>& filenames);

  string getRoot();
  vector<string> getNeighbor(const string& vertex);
  const unordered_map<string, vector<string>>& getNodes();

  void setRoot(const string& new_root);
  void printInfo();
  vector<string> dfs();
  void pageRank();

 private:
  unordered_map<string, vector<string>> nodes_;
  unordered_set<string> all_nodes_;
  unordered_map<string, int> urlToIndex_;
  string root_;

  void addFileInfoToGraph(const string& filename);

  static vector<string> split(const string& to_split, const string& del);
  static void smartTrim(vector<string>& to_trim);
};