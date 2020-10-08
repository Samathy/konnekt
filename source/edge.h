#include <memory>

class vertex;
/** Edge class
 * Represents an edge of the graph.
 * Basically only contains pointers to the edge's connected vertices.
 */

class edge {
public:
  edge(std::shared_ptr<vertex> v1, std::shared_ptr<vertex> v2) {

    this->v1 = v1;
    this->v2 = v2;
  }

  /** Get the first vertex
   * Note: ideally this would be a property, instead of a function.
   */
  const std::shared_ptr<vertex> getV1() { return this->v1; }

  /** Get the second vertex
   * Note: ideally this would be a property, instead of a function.
   */
  const std::shared_ptr<vertex> getV2() { return this->v2; }

private:
  std::shared_ptr<vertex> v1;
  std::shared_ptr<vertex> v2;
};
