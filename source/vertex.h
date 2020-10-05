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

  /** Add a label to this vertex. Vertices can have many labels */
  void addLabel(const std::string label) { this->labels.push_back(label); }

  /** Remove given label from this vertex.
   * Return true if successful.
   * Return false if not found
   */
  bool removeLabel ( const std::string label )
  {

  }

  /** Check if this vertex has a given label
   * Returns true if found
   * Returns false if non-existant
   */
  bool hasLabel(const std::string toFind) {

    auto l = std::find(this->labels.begin(), this->labels.end(), toFind);
    if (l != this->labels.end())
      return true;

    return false;
  }

private:
  std::vector<std::string> labels;
};
