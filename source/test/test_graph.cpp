#include "catch2/catch.hpp"

#include "../graph.h"

TEST_CASE("test_add_vertex")
{

    graph g = graph();

    auto v = g.createVertex();

    REQUIRE(g.size() == 1);

}

TEST_CASE("test_find_vertex")
{

    graph g = graph();
    auto v = g.createVertex();

    v->addLabel("Testing");

    auto found = g.findVertex("Testing");

    REQUIRE(found.size() > 0);
    
    //They should be the same shared pointer.
    REQUIRE(v == found[0]);

}


TEST_CASE("test_add_edge")
{
    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    auto v1 = g.createVertex();
    v1->addLabel("Testing");

    auto e = g.createEdge(v, v1);

    REQUIRE(v->getEdges().size() == 1);
    REQUIRE(v1->getEdges().size() == 2);

    REQUIRE(v->getEdges()[0] == e);
    REQUIRE(v1->getEdges()[0] == e);
}

TEST_CASE("test_find_edge")
{
    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    auto v1 = g.createVertex();
    v1->addLabel("Testing");

    auto e = g.createEdge(v, v1);

    auto edges = g.findEdges(v, v1);

    REQUIRE(edges.size() == 1);
    REQUIRE(edges[0] == e);
}
