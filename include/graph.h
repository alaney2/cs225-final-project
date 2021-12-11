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
  /**
   *  Constructor if all data is coming from a single file
   * @param filename the file to read data from
   */
  explicit Graph(const string& filename);

  /**
   * Constructor to use if data is coming from multiple files
   * @param filenames vector of files to read data from
   */
  explicit Graph(const vector<string>& filenames);

  /**
   * get the current root node of the graph
   * @return current root as a string
   */
  string getRoot();

  /**
   * Getter for all the neighbors of a given node
   * @param vertex the node that you want all the neighbors of
   * @return vector of strings of neighbors to node that has the title vertex
   */
  vector<string> getNeighbor(const string& vertex);

  /**
   * Getter to get all Nodes in the graph, used for testing
   * @return unordered map where each key is a node value and each value pair
   *         for a key is a vector of neighbors stored as their node value
   */
  const unordered_map<string, vector<string>>& getNodes();

  /**
   * Changes the root of the graph, root is the default location to start
   * for pagerank and DFS traversal, changing this changes the default
   * start location and can change the output as a result.
   * @param new_root string name of new root
   */
  void setRoot(const string& new_root);

  /**
   * Prints formatted information about the entire current graph.
   */
  void printInfo();
  
  /**
   * Traverse the graph starting from the current root
   * @return vector of strings of the order the nodes the graph was traversed in
   */
  vector<string> dfs();

  /**
   * Get the steady steady state rank of the page rank algorithm after 50
   * iterations. The start vector has 1 for the start node and 0 for all
   * other values with the start node being the root
   * @return vector of strings from highest likelihood to lowest according
   *         to pagerank
   */
  vector<string> pageRank();

  /**
   * Exact same as above page rank except the start node is at an
   * arbitrary node instead of the root
   * @param start_node desired start node for start vector
   * @return vector of strings from highest likelihood to lowest according to
   *         pagerank
   */
  vector<string> pageRank(const string& start_node);

  /**
   * Return an adjacency matrix representation of the graph, used for pagerank,
   * is public for testing purposes
   * @return matrix represented by a 2d vector
   */
  vector<vector<double>> genAdjacency();

  /**
   * Given a url the corresponding index of the adjacency matrix is given. Is
   * public for testing test pagerank implementation.
   * @param url the url to get the desired index of
   * @return the desired index
   */
  int getIndexFromUrl(const string& url);

  /**
   * Makes the page rank matrix where each column sums to 1, if everything is 0,
   * each entry in a column is 1/(num entries in column), else each entry is
   * (entry)/(num non-zero entries in column). Is public for testing purposes
   * @param m adjacency matrix
   * @return page rank matrix
   */
  vector<vector<double>> genPageRankMatrix(const vector<vector<double>>& m);

  /**
   * Multiplies a square matrix and a vector together, used for pagerank. Is
   * public for testing purposes.
   * @param m matrix
   * @param v vector
   * @return results of M times v
   */
  static vector<double> multMatrixWithVector(const vector<vector<double>>& m,
                                             const vector<double>& v);
  
  /**
   * 
   * @return set of strongly connected components (sets of vertices)
   */
  unordered_set<vector<string>> tarjan();
  
  /**
   * Set the depth index for node to the smallest unused index
   * @param node 
   * @param index node index
   * @param index_map map of nodes to their indices
   * @param low_link_map map of nodes to the smallest index of any node reachable from that node
   * @param on_stack keeps track of if nodes have been added to the stack
   * @param stack stack of nodes to visit
   */
  void strongConnect(const string& node,
                     size_t& index,
                     unordered_map<string, size_t>& index_map,
                     unordered_map<string, size_t>& low_link_map,
                     unordered_map<string, bool>& on_stack,
                     stack<string>& stack,
                     unordered_set<vector<string>>& res);
  

 private:
  /**
   * Main graph structure, each key is a string that represents a node,
   * each value pair is a vector of neighbor nodes
   */
  unordered_map<string, vector<string>> nodes_;

  /**
   * Stores same information as nodes_ above, this is used during the
   * data parsing process to catch any edge nodes that are not part of the
   * cs.illinois.edu/cs225/fall2021 domain but are connected to pages in that
   * domain.
   */
  unordered_set<string> all_nodes_;

  /**
   * Map that has as a key a node value of the graph, and as a value a unique
   * index for that node. Used for adjacency and pagerank matrices
   */
  unordered_map<string, int> url_to_index_;

  /**
   * Inverse structure as url_to_index_, the indices of the vector correspond
   * to a a unique string which is the representation of a node
   */
  vector<string> index_to_url_;

  /**
   * Current root of graph, default start for dfs and pagerank
   */
  string root_;

  /**
   * Helper that prints a matrix that is represented as a 2d vector
   * @param m matrix to print
   */
  void printMatrix(vector<vector<double>> m);

  /**
   * Helper for the constructors which adds all the information from
   * one file to the graph
   * @param filename desired file to add information from
   */
  void addFileInfoToGraph(const string& filename);

  /**
   * Helper for page rank that sets all values of a column of a matrix
   * represented as 2d vector to a specific value
   * @param m matrix to change
   * @param col column to change
   * @param val value to set each location in column to
   */
  static void setColumnToValue(vector<vector<double>>& m, size_t col,
                               double val);

  /**
   * Helper for page rank that divides all values in column of a matrix
   * represented as a 2d vector by a value
   * @param m matrix to change
   * @param col column to change
   * @param val value to divide each column in matrix by
   */
  static void divideColumnByValue(vector<vector<double>>& m, size_t col,
                                  double val);

  /**
   * Helper used to parse data from files, splits a string on a deliminator
   * @param to_split a string to split
   * @param del text to split the string around
   * @return vector of the original string split around the deliminator
   */
  static vector<string> split(const string& to_split, const string& del);

  /**
   * Helper used to clean individual entries of node names read from files.
   * Removes excess space, commas, and slashes from the start and
   * end of urls. Change is in place
   * @param to_trim the string to trim
   */
  static void smartTrim(vector<string>& to_trim);
};