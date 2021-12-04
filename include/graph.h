//
// Created by becla on 12/4/2021.
//
#pragma once

#include <string>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

class Graph {
 public:
  Graph(string filename);
  
  string getRoot();
  vector<string> getNeighbor(string vertex);

 private:
  map<string, vector<string>> nodes;
  string root;
};