#include <memory>
#include <string_view>
#include <vector>

#include "edge.h"
#include "vertex.h"

class graph {
public:
  graph() {}

  /** Create a new vertex in the graph
   * Returns: A shared pointer to the new vertex object
   */
  std::shared_ptr<vertex> createVertex() {
    std::shared_ptr<vertex> ret(new vertex());
    return ret;
  }

  /** Create a new edge connected to given vertices
   * Returns: A shared pointer to the new edge
   */
  std::shared_ptr<edge> createEdge(std::shared_ptr<vertex> v1,
                                   std::shared_ptr<vertex> v2) {
    std::shared_ptr<edge> ret(new edge(v1, v2));
    return ret;
  }

  /** Find a vertex by label.
   * Returns: A list of verticies with the given label.
   * If none are found, the list is empty.
   */
  std::vector<std::shared_ptr<vertex>> findVertex(std::string label) {
    std::shared_ptr<vertex> v(new vertex());
    std::vector<std::shared_ptr<vertex>> ret = {v};
    return ret;
  }

  /** Find an edge between two given vertices
   * Returns a list of edges that exist between two verticies.
   * It is unlikely that there will be more than one edge.
   */
  std::vector<std::shared_ptr<edge>> findEdges(std::shared_ptr<vertex> v1,
                                               std::shared_ptr<vertex> v2) {
    std::shared_ptr<edge> e(new edge(v1, v2));
    std::vector<std::shared_ptr<edge>> ret;
    ret.push_back(e);
    return ret;
  }

  /** Generates a dot graph of the stored graph.
   * This has to walk the graph, and can be very expensive on large graphs.
   */
  std::string_view getDot() { return std::string_view(this->dot); }

  size_t size() { return 0; }

private:
  /* Using vectors is probably not great for searching for a given vertex
   * to delete it, or start a search from it.
   * Perhaps vertices should have an ID, and we should store them in a tree,
   * or a hash-map or something like that. Optimise later, maybe.
   */
  std::vector<std::shared_ptr<vertex>> vertices;
  std::vector<std::shared_ptr<edge>> edges;

  std::string dot;
};
