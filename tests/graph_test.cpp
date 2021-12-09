//
// Created by becla on 12/4/2021.
//
#include "../include/graph.h"

#include <algorithm>

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
    REQUIRE(res.size() == 11);
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

