#include <algorithm>
#include <memory>
#include <sstream>
#include <string_view>
#include <vector>

#include "edge.h"
#include "vertex.h"

/** Class containing the results of a shortest-path check */
class dijkstra_result {
public:
  std::shared_ptr<vertex> v1;
  std::shared_ptr<vertex> v2;

  std::vector<std::shared_ptr<vertex>>
      vertices; // Vertices along the path in order of visitation
  std::vector<std::shared_ptr<edge>>
      edges; // Edges along the path in order of visitation

  bool path_exists = false;

  /** Traceback the edges as well. This could take time and might not be a very
   * useful operation to do all at once. You probably just want to do it lazily
   */
  std::vector<std::shared_ptr<edge>> fillEdges() { return this->edges; }
};

class graph {
public:
  graph() {}

  /** Create a new vertex in the graph
   * Returns: A shared pointer to the new vertex object
   */
  std::shared_ptr<vertex> createVertex() {
    std::shared_ptr<vertex> ret(new vertex(this->idMax + 1));
    this->vertices.push_back(ret);
    this->idMax += 1;
    return ret;
  }

  /** Create a new edge connected to given vertices
   * Returns: A shared pointer to the new edge
   */
  std::shared_ptr<edge> createEdge(std::shared_ptr<vertex> v1,
                                   std::shared_ptr<vertex> v2) {
    std::shared_ptr<edge> ret(new edge(v1, v2));
    this->edges.push_back(ret);

    v1->addEdge(ret);
    v2->addEdge(ret);

    return ret;
  }

  /** Find a vertex by label.
   * Returns: A list of verticies with the given label.
   * If none are found, the list is empty.
   */
  std::vector<std::shared_ptr<vertex>> findVertex(std::string label) {
    std::vector<std::shared_ptr<vertex>> ret;

    // Linear complexity - but we can't really do better than that on an
    // unsorted vector
    std::for_each(this->vertices.begin(), this->vertices.end(),
                  [label, &ret](std::shared_ptr<vertex> &v) {
                    if (v->hasLabel(label))
                      ret.push_back(v);
                  });

    return ret;
  }

  /** Find an edge between two given vertices
   * Returns a list of edges that exist between two verticies.
   * It is unlikely that there will be more than one edge.
   *
   * Probably slowish with lots of edges because linear search :(
   */
  std::vector<std::shared_ptr<edge>> findEdges(std::shared_ptr<vertex> v1,
                                               std::shared_ptr<vertex> v2) {

    std::vector<std::shared_ptr<edge>> ret;
    std::for_each(this->edges.begin(), this->edges.end(),
                  [v1, v2, &ret](std::shared_ptr<edge> e) {
                    if (e->getV1() == v1 && e->getV2() == v2)
                      ret.push_back(e);
                  });

    return ret;
  }

  /** Generates a dot graph of the stored graph.
   * This has to walk the graph, and can be very expensive on large graphs.
   */
  std::string_view getDot() {

    std::stringstream ss;

    if (this->dot.empty()) {
      ss << "graph { " << std::endl;
      std::for_each(
          this->edges.begin(), this->edges.end(),
          [&ss](std::shared_ptr<edge> e) {
            std::shared_ptr<vertex> v1(e->getV1());
            std::shared_ptr<vertex> v2(e->getV2());

            ss << v1->getID() << "[style=dashed, label=\"" << v1->getID() << ":"
               << v1->getLabelsAsString() << "\"];" << std::endl;
            ss << v2->getID() << "[style=dashed, label=\"" << v2->getID() << ":"
               << v2->getLabelsAsString() << "\"];" << std::endl;
            ss << v1->getID() << " -- " << v2->getID() << ";" << std::endl;
          });

      ss << "}";

      this->dot = ss.str();
    }

    return this->dot;
  }

  /** Calculate the shortest path between two nodes.
   *
   * Returns a 'dijkstra_result' object */
  const dijkstra_result shortest_path(std::shared_ptr<vertex> v1,
                                      std::shared_ptr<vertex> v2) {
    // Reset any dijkstra related labels on the vertices
    std::for_each(this->vertices.begin(), this->vertices.end(),
                  [](std::shared_ptr<vertex> v) { v->dijkstraReset(); });

    std::vector<std::shared_ptr<vertex>> unvisited(this->vertices);
    std::vector<std::shared_ptr<vertex>> visited;

    v1->dijkstraSetDistance(0);

    std::shared_ptr<vertex> current_vertex = v1;
    int current_vertex_i = 0;

    bool complete = false;

    dijkstra_result result;

    while (!unvisited.empty()) {

      if (current_vertex == v2) {
        complete = true;
        break;
      }

      std::vector<std::shared_ptr<edge>> current_edges =
          current_vertex->getEdges();
    
      if ( current_edges.size() == 0)
      {
          continue;
      }

      for (auto &edge : current_edges) {
        std::shared_ptr<vertex> other_vertex = edge->getOther(current_vertex);
        if (other_vertex->dijkstraGetDistance() <
            current_vertex->dijkstraGetDistance())
          other_vertex->dijkstraSetDistance(
              other_vertex->dijkstraGetDistance() +
              current_vertex->dijkstraGetDistance());
      }

      auto it = std::find(unvisited.begin(), unvisited.end(), current_vertex);

      // explode here if the vertex isnt in unvisited!
      unvisited.erase(it);
      current_vertex->dijkstraSetVisited();
      visited.push_back(current_vertex);

      int smallest_distance = 0;
      std::shared_ptr<vertex> next_vertex;

      for (auto &edge : current_edges) {
        std::shared_ptr<vertex> other_vertex = edge->getOther(current_vertex);
        if (other_vertex->dijkstraGetDistance() < smallest_distance)
        {
          smallest_distance = other_vertex->dijkstraGetDistance();
          next_vertex = other_vertex;
        }

      }

      current_vertex = next_vertex;
    }

    if (complete = true) {
      result.v1 = v1;
      result.v2 = v2;

      result.path_exists = true;

      result.vertices = visited;
      result.vertices.push_back(v2);
    }

    return result;
  }

  size_t size() { return this->vertices.size(); }

private:
  /* Using vectors is probably not great for searching for a given vertex or
   * edge to delete things, or start a search from from a vertex to another one.
   * Perhaps vertices should have an ID, and we should store them in a tree,
   * or a hash-map or something like that. Has to be able to cope with vertexs
   * being removed though.
   * We could do a whole adjacency matrix thing with enough time, and no need to
   * delete verticies. Optimise later maybe.
   */
  std::vector<std::shared_ptr<vertex>> vertices;
  std::vector<std::shared_ptr<edge>> edges;

  std::string dot;

  int idMax = 0; /** The current max ID number */
};
