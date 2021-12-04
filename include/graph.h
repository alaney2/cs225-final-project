//
// Created by becla on 12/4/2021.
//
#pragma once

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

class Graph {
 public:
  explicit Graph(const string& filename);
  explicit Graph(const vector<string>& filenames);
  
  string getRoot();
  vector<string> getNeighbor(const string& vertex);

  void setRoot(const string& new_root);
  void printInfo();

 private:
  unordered_map<string, vector<string>> nodes;
  string root;

  void addFileInfoToGraph(const string& filename);
};