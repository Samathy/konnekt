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

  /** Construct with one label*/
  vertex(std::string label) {
      this->labels.push_back(label);
  }

  /** Construct with many labels */
  vertex(std::vector<std::string> labels) {
      //This could be a move, instead of a copy. idk if that'd improve  memory usage for large lists of labels
      this->labels.insert(this->labels.end(), labels.begin(), labels.end());
  }

  /** Add a label to this vertex. Vertices can have many labels */
  void addLabel(const std::string label) { this->labels.push_back(label); }

  /** Remove given label from this vertex.
   * Return true if successful.
   * Return false if not found
   */
  bool removeLabel ( const std::string label )
  {
    if (!this->labels.size()) //dont even bother searching if we have no labels
        return false;

    auto l = std::find(this->labels.begin(), this->labels.end(), label);
    if (l != this->labels.end()) {
        this->labels.erase(l);
        return true;
    }

    return false;
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
