#include <iostream>

#include "include/graph.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
  vector<string> data_files = {"data1.txt", "data2.txt"};

  Graph g = Graph(data_files);
  g.setRoot("https://courses.engr.illinois.edu/cs225/fa2021");

  vector<string> vdfs = g.dfs();
  cout << "DFS Traversal:"<<endl;
  for(auto &a : vdfs){
    cout << a << " -> ";
  }
  cout << endl; cout << endl;

  cout << "Algorithm #1: PageRank" << endl;
  int idx = 1;
  const auto& page_rank_res = g.pageRank();
  for (size_t i = 0; i < 50; ++i) {
    if(page_rank_res[i] == "") continue;
    cout << idx << ": " << page_rank_res[i] << endl;
    idx ++;
  }
  cout << endl;

  cout << "Algorithm #2: Tarjan's Strongly Connect Component Algorithm" <<endl;



  return 0;
}
