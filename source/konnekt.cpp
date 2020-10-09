#include "ingest.h"
#include <iostream>

int main(int argc, char **argv) {
  std::unique_ptr<graph> g;
  if (argc >= 1) {
    std::cout << "Ingesting graph from: " << argv[1] << std::endl;
    g = ingest_json(argv[1]);
  } else {
    std::cout << "Ingesting graph from exmaple1.json";
    g = ingest_json("example1.json");
  }

  if (std::string(argv[2]) == "--shortest-path") {
    if (argc >= 4) {
      std::string v1_label = std::string(argv[3]);
      std::string v2_label = std::string(argv[4]);

      std::cout << "Finding shortest path between nodes withlabels: "
                << v1_label << " and " << v2_label << std::endl;

      auto result = g->shortest_path(g->findVertex(v1_label)[0],
                                     g->findVertex(v2_label)[0]);

      if (result.path_exists) {
        std::cout << "Path exists" << std::endl;
        for (auto &vertex : result.vertices) {
          std::cout << vertex->getID() << ":" << vertex->getLabelsAsString()
                    << std::endl;
          std::cout << "    v    " << std::endl;
        }
      } else
        std::cout << "Path does not exist";

      return 0;
    }
  }

  if (std::string(argv[2]) == "--dot") {
    std::cout << g->getDot();
  }

  return 0;
}
