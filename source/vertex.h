#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

class edge;

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

  vertex(int id) { this->id = id; }

  /** Construct with one label*/
  vertex(std::string label) { this->labels.push_back(label); }

  /** Construct with many labels */
  vertex(std::vector<std::string> labels) {
    // This could be a move, instead of a copy. idk if that'd improve  memory
    // usage for large lists of labels
    this->labels.insert(this->labels.end(), labels.begin(), labels.end());
  }

  /** Add a label to this vertex. Vertices can have many labels */
  void addLabel(const std::string label) { this->labels.push_back(label); }

  /** Remove given label from this vertex.
   * Return true if successful.
   * Return false if not found
   */
  bool removeLabel(const std::string label) {
    if (!this->labels.size()) // dont even bother searching if we have no labels
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

  void addEdge(std::shared_ptr<edge> e) { this->edges.push_back(e); }

  /** Get all labels attached to this vertex */
  const std::vector<std::string> getLabels()
  {
      return this->labels;
  }

  const int getID()
  {
      return this->id;
  }

  /** Return this vertex's labels as a string */
  const std::string getLabelsAsString()
  {
    std::stringstream ss;
    ss << "[";
    std::for_each(this->labels.begin(), this->labels.end(),
            [&ss](std::string l)
            {
                ss << l << ", ";
            });
    ss << "]";
    return ss.str();
  }


  size_t countEdges() { return this->edges.size(); }

  const std::vector<std::shared_ptr<edge>> getEdges() const {
    // Does copying the list of shared pointers take a lot of time/memory?
    // Would it be better to return const pointer to the vector instead of a
    // const copy?
    return this->edges;
  }

private:
  std::vector<std::string> labels;
  std::vector<std::shared_ptr<edge>> edges;

  int id;
};
