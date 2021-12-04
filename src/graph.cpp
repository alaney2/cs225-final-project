#include "../include/graph.h"

#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;

Graph::Graph(string filename) {
  string line;
  ifstream file(filename);
  string url = "";
  bool flag = 1;
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
    cout << "Could not open file." << endl;
  }
}
string Graph::getRoot() { return root; }
vector<string> Graph::getNeighbor(string vertex) { return nodes[vertex]; }
