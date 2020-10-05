#include "catch2/catch.hpp"
#include "../vertex.h"

TEST_CASE("test_set_vertex_label")
{

    vertex v = vertex();

    v.addLabel("Testing");

    REQUIRE(v.hasLabel("Testing"));
}

TEST_CASE ("test_remove_vertex_label")
{
    vertex v = vertex();

    v.addLabel("Testing");
    
    REQUIRE(v.hasLabel("Testing"));

    v.removeLabel("Testing");

    REQUIRE_FALSE(v.hasLabel("Testing"));
}
