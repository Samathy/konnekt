#include <algorithm>
#include <string>
#include <vector>

/** Vertex class
 * Represents a vertex/node on the graph.
 * Nodes may have one or more labels, which can be set, removed and retrieved.
 * Vertex's also contain a list of edges connected to other vertexes.
 *
 * A vertex is responsible for deleting it's own reference to an edge.
 */
class vertex {

public:
  vertex() {}

  vertex(std::string label) {}

  vertex(std::vector<std::string> labels) {}

  void addLabel(const std::string label) {}

  bool hasLabel(const std::string toFind) { return false; }

private:
  std::vector<std::string> labels;
};
