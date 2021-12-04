#include <iostream>

#include "include/graph.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  Graph g = Graph("data1.txt");
  string root = g.getRoot();
  cout << "root-- " << root << endl;
  vector<string> n = g.getNeighbor(root);
  for (auto i : n) {
    cout << i << " || ";
  }
  cout << endl;

//  while (true) {
//    string search;
//    cout << "Enter new url: " << endl;
//    cin >> search;
//    vector<string> n2 = g.getNeighbor(search);
//    for (auto i : n2) {
//      cout << i << " || ";
//    }
//    cout << endl;
//  }
  return 0;
}