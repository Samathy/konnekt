#include "catch2/catch.hpp"

#include "../graph.h"


TEST_CASE("test_create_vertex")
{

    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    REQUIRE(g.size() == 1);

    REQUIRE(g.findVertex("Testing")[0] == v);

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


TEST_CASE("test_create_edge")
{
    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    auto v1 = g.createVertex();
    v1->addLabel("Testing");

    auto e = g.createEdge(v, v1);

    REQUIRE(v->getEdges().size() == 1);
    REQUIRE(v1->getEdges().size() == 1);

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

TEST_CASE("test_vertices_created_with_incrementing_id")
{
    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    auto v1 = g.createVertex();
    v1->addLabel("Testing");

    REQUIRE(v->getID() == 1);
    REQUIRE(v1->getID() == 2);

}

TEST_CASE("test_generate_dot_graph")
{

    std::string dot_expected = "graph { \n1[style=dashed, label=\"1:<Testing, >\"];\n2[style=dashed, label=\"2:<Testing1, >\"];\n1 -- 2;\n}";

    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    auto v1 = g.createVertex();
    v1->addLabel("Testing1");

    auto e = g.createEdge(v, v1);

    std::string_view dot = g.getDot();

    REQUIRE(dot == dot_expected);
}

TEST_CASE("test_dijkstra")
{
    graph g = graph();

    auto v = g.createVertex();
    v->addLabel("Testing");

    auto v1 = g.createVertex();
    v1->addLabel("Testing1");

    auto v2 = g.createVertex();
    v1->addLabel("Testing2");

    auto v3 = g.createVertex();
    v1->addLabel("Testing3");

    g.createEdge(v, v1);
    g.createEdge(v1, v3);

    g.createEdge(v, v1);
    g.createEdge(v1, v2);
    g.createEdge(v2, v3);

    auto path = g.shortest_path(v, v3);
    
    std::vector<std::shared_ptr<vertex>> shortest_path_expected;
    shortest_path_expected.push_back(v);
    shortest_path_expected.push_back(v1);
    shortest_path_expected.push_back(v3);

    REQUIRE(path.vertices == shortest_path_expected);
}
