#include <memory>

class vertex;
/** Edge class
 * Represents an edge of the graph.
 * Basically only contains pointers to the edge's connected vertices.
 */

class edge {
public:
  edge(std::shared_ptr<vertex> v1, std::shared_ptr<vertex> v2) {}

  std::shared_ptr<vertex> getv1() {
    std::shared_ptr<vertex> ret(new vertex());
    return ret;
  }
};
