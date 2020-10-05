#include "catch2/catch.hpp"
#include "../vertex.h"

TEST_CASE("test_set_vertex_label")
{

    vertex v = vertex();

    v.addLabel("Testing");

    REQUIRE(v.hasLabel("Testing"));
}
