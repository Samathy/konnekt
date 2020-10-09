#include "catch2/catch.hpp"

#include <memory>

#include "../vertex.h"
#include "../edge.h"

TEST_CASE("test_get_other_vertex")
{

    std::shared_ptr<vertex> v = std::make_shared<vertex>();
    std::shared_ptr<vertex> v1 = std::make_shared<vertex>();

    v->addLabel("Testing");
    v1->addLabel("Testing2");

    edge e = edge(v,v1);

    REQUIRE(e.getOther(v) == v1);
    REQUIRE(e.getOther(v1) == v);
}


    
