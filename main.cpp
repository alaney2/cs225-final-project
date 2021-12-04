#include <iostream>

#include "include/graph.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  vector<string> data_files = {"data1.txt", "data2.txt"};

  Graph g = Graph(data_files);
  g.setRoot("https://courses.engr.illinois.edu/cs225/fa2021");

  //  g.printInfo();

  string root = g.getRoot();
  cout << "root-- " << root << endl;
  vector<string> n = g.getNeighbor(root);
  for (const auto& i : n) {
    cout << i << " || ";
  }
  cout << endl << endl;

  // Error in current parser: main nodes don't include end slash but in the
  // neighbor list they do

  while (true) {
    string search = "";
    cout << "Enter new url: " << endl;
    cin >> search;
    cout << "Your Search: " << search << endl;
    vector<string> n2 = g.getNeighbor(search);
    for (auto i : n2) {
      cout << i << " || ";
    }
    cout << endl;
  }
  return 0;
}
