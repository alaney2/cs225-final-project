//
// Created by becla on 12/4/2021.
//
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

using std::string;
using std::unordered_map;
using std::vector;
using std::stack;

class Graph {
 public:
  explicit Graph(const string& filename);
  explicit Graph(const vector<string>& filenames);
  
  string getRoot();
  vector<string> getNeighbor(const string& vertex);

  void setRoot(const string& new_root);
  void printInfo();
  void dfs();
  void pageRank();

 private:
  unordered_map<string, vector<string>> nodes;
  string root;

  void addFileInfoToGraph(const string& filename);
};