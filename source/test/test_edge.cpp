#include "catch2/catch.hpp"

#include "../vertex.h"
#include "../edge.h"

TEST_CASE("test_get_other_vertex")
{

    vertex v = vertex();
    vertex v1 = vertex();

    v.addLabel("Testing");
    v1.addLabel("Testing2");

    edge e = edge(v,v1);

    REQUIRE(e.getOther(v) == v1);
    REQUIRE(e.getOther(v1) == v);
}


    
