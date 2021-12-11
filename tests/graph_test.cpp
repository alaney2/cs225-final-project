//
// Created by becla on 12/4/2021.
//
#include "../include/graph.h"

#include <algorithm>
#include <iostream>

#include "../catch/catch.hpp"

TEST_CASE("Sanity Parser Checks") {
  SECTION("Single input does not crash parser") {
    Graph g1("tests/test_data/test_data1.txt");
    Graph g2(std::vector<string>({"tests/test_data/test_data1.txt"}));
    REQUIRE(true);
  }

  SECTION("No input does not crash parser") {
    Graph g1("");
    Graph g2(std::vector<string>({""}));
    REQUIRE(true);
  }

  SECTION("Invalid File not crash parser") {
    Graph g(std::vector<string>({"This_File_Does_Not_exist.txt"}));
    REQUIRE(true);
  }

  SECTION("Two inputs does not crash parser") {
    Graph g(std::vector<string>(
        {"tests/test_data/test_data1.txt", "tests/test_data/test_data2.txt"}));
    REQUIRE(true);
  }

  SECTION("Empty File does not crash parser") {
    Graph g(std::vector<string>({"tests/test_data/test_data3.txt"}));
    REQUIRE(true);
  }

  SECTION("Three inputs does not crash parser") {
    Graph g(std::vector<string>({"tests/test_data/test_data1.txt",
                                 "tests/test_data/test_data2.txt",
                                 "tests/test_data/test_data4.txt"}));
    REQUIRE(true);
  }

  SECTION("Three inputs, 2 valid, 1 invalid does not does not crash parser") {
    Graph g2(std::vector<string>({"tests/test_data/test_data1.txt",
                                  "tests/test_data/test_data2.txt",
                                  "tests/test_data/test_data3.txt"}));
    REQUIRE(true);
  }
}

TEST_CASE("Parser Tests") {
  using std::find;

  SECTION("Reads Node data correctly") {
    vector<string> data_files = {"tests/test_data/test_data1.txt"};
    Graph g(data_files);
    const auto& nodes = g.getNodes();

    REQUIRE(nodes.size() == 6);
    REQUIRE(nodes.find("google.com") != nodes.end());
    REQUIRE(nodes.find("gmail.com") != nodes.end());
    REQUIRE(nodes.find("illinois.edu") != nodes.end());
    REQUIRE(nodes.find("outlook.com") != nodes.end());
    REQUIRE(nodes.find("microsoft.com") != nodes.end());
    REQUIRE(nodes.find("netflix.com") != nodes.end());
  }

  SECTION("Stores Neighbors Correctly") {
    Graph g("tests/test_data/test_data1.txt");
    const auto& nodes = g.getNodes();

    const auto& n1 = nodes.find("google.com")->second;
    const auto& n2 = nodes.find("gmail.com")->second;

    REQUIRE(n1.size() == 2);
    REQUIRE(find(n1.begin(), n1.end(), "gmail.com") != n1.end());
    REQUIRE(find(n1.begin(), n1.end(), "illinois.edu") != n1.end());
    REQUIRE(find(n1.begin(), n1.end(), "fakeSite.com") == n1.end());

    REQUIRE(n2.size() == 3);
    REQUIRE(find(n2.begin(), n2.end(), "outlook.com") != n2.end());
    REQUIRE(find(n2.begin(), n2.end(), "microsoft.com") != n2.end());
    REQUIRE(find(n2.begin(), n2.end(), "netflix.com") != n2.end());
    REQUIRE(find(n2.begin(), n2.end(), "fakeSite.com") == n2.end());
  }

  SECTION("Test Parser Helper Methods") {
    Graph g("tests/test_data/test_data4.txt");
    const auto& nodes = g.getNodes();

    SECTION("Trim from main Node") {
      REQUIRE(nodes.find("https://outlook.office.com/") == nodes.end());
      REQUIRE(nodes.find("https://outlook.office.com") != nodes.end());
    }

    SECTION("Trim Multiple from main Node") {
      REQUIRE(nodes.find("https://outlook.com//") == nodes.end());
      REQUIRE(nodes.find("https://outlook.com") != nodes.end());
    }

    SECTION("Trim from neighbor nodes") {
      const auto& n = nodes.find("https://outlook.office.com")->second;
      REQUIRE(n.size() == 2);

      REQUIRE(find(n.begin(), n.end(), "https://outlook.com//") == n.end());
      REQUIRE(find(n.begin(), n.end(), "hololens.com/") == n.end());

      REQUIRE(find(n.begin(), n.end(), "https://outlook.com") != n.end());
      REQUIRE(find(n.begin(), n.end(), "hololens.com") != n.end());
    }
  }
}

TEST_CASE("DFS Simple") {
  Graph g("tests/test_data/test_data1.txt");

  SECTION("Root at most connected node") {
    g.setRoot("google.com");
    auto res = g.dfs();
    REQUIRE(res.size() == 6);
  }

  SECTION("Root at middle node") {
    g.setRoot("gmail.com");
    auto res = g.dfs();
    REQUIRE(res.size() == 4);
  }

  SECTION("Root at edge node") {
    g.setRoot("netflix.com");
    auto res = g.dfs();
    REQUIRE(res.size() == 1);
  }
}

TEST_CASE("DFS Across Multiple Files") {
  vector<string> data_files = {
      "tests/test_data/test_data1.txt", "tests/test_data/test_data2.txt",
      "tests/test_data/test_data3.txt", "tests/test_data/test_data4.txt"};
  Graph g(data_files);
  SECTION("Root at most connected node") {
    g.setRoot("google.com");
    auto res = g.dfs();
    REQUIRE(res.size() == 10);
  }

  SECTION("Root at a middle node") {
    g.setRoot("azure.com");
    auto res = g.dfs();
    REQUIRE(res.size() == 6);
  }

  SECTION("Root at edge node") {
    g.setRoot("netflix.com");
    auto res = g.dfs();
    REQUIRE(res.size() == 1);
  }
}

TEST_CASE("Page Tests") {
  Graph graph("tests/test_data/test_data5.txt");
  graph.setRoot("google.com");
  int a = graph.getIndexFromUrl("amazon.com");
  int g = graph.getIndexFromUrl("google.com");
  int f = graph.getIndexFromUrl("facebook.com");
  int y = graph.getIndexFromUrl("youtube.com");
  int t = graph.getIndexFromUrl("twitter.com");
  int w = graph.getIndexFromUrl("wikipedia.com");
  SECTION("Adjacency Test") {
    const auto& matrix = graph.genAdjacency();

    // matrix[j, i] means from i to j
    REQUIRE(matrix[y][g] == 1);
    REQUIRE(matrix[f][g] == 1);

    REQUIRE(matrix[w][f] == 1);
    REQUIRE(matrix[w][f] == 1);

    REQUIRE(matrix[w][a] == 1);
    REQUIRE(matrix[t][a] == 1);
    REQUIRE(matrix[y][a] == 1);

    REQUIRE(matrix[g][w] == 1);

    REQUIRE(matrix[y][t] == 1);

    REQUIRE(matrix[g][y] == 1);
  }

  SECTION("Weight Adjust Matrix") {
    const auto& matrix = graph.genPageRankMatrix(graph.genAdjacency());
    REQUIRE(matrix[y][g] == 0.5);
    REQUIRE(matrix[f][g] == 0.5);

    REQUIRE(matrix[w][f] == 0.5);
    REQUIRE(matrix[w][f] == 0.5);

    REQUIRE(matrix[w][a] == Approx(0.33333).epsilon(0.001f));
    REQUIRE(matrix[t][a] == Approx(0.33333).epsilon(0.001f));
    REQUIRE(matrix[y][a] == Approx(0.33333).epsilon(0.001f));

    REQUIRE(matrix[g][w] == 1);

    REQUIRE(matrix[y][t] == 1);

    REQUIRE(matrix[g][y] == 1);
  }

  SECTION("Multiplying Matrix and Vector") {
    vector<vector<double>> m = {{0.7, 0.8}, {0.9, 0.2}};
    vector<double> v = {0.2, 0.5};
    const auto& res = graph.multMatrixWithVector(m, v);
    REQUIRE(res[0] == 0.7 * 0.2 + 0.8 * 0.5);
    REQUIRE(res[1] == 0.9 * 0.2 + 0.2 * 0.5);
  }

  // in this test the start location does not matter since the steady
  // state should always end up being the same
  SECTION("All Page Rank Together") {
    for (const auto& possible_root : graph.getNodes()) {
      graph.setRoot(possible_root.first);
      const auto& res = graph.pageRank();
      REQUIRE(res[0] == "google.com");
      REQUIRE(res[1] == "youtube.com");
      REQUIRE(res[2] == "facebook.com");
      REQUIRE(res[3] == "wikipedia.com");
      REQUIRE(res[4] == "amazon.com");
      REQUIRE(res[5] == "twitter.com");
    }
  }
}

TEST_CASE("tarjan") {
  //  Graph graph("tests/test_data/test_data5.txt");
  //  graph.setRoot("google.com");
  //  graph.printInfo();
  //
  vector<string> data_files = {"data1.txt", "data2.txt"};

  Graph graph = Graph(data_files);
  graph.setRoot("https://courses.engr.illinois.edu/cs225/fa2021");
  const auto& res = graph.tarjan();
  for (const auto& v : res) {
    std::cout << "Component: " << std::endl;
    for (const auto& s : v) {
      std::cout << s << ", ";
    }
    std::cout << std::endl << std::endl;
  }
}