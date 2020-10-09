#include "catch2/catch.hpp"

#include "../vertex.h"
#include "../edge.h"

TEST_CASE("test_set_vertex_label")
{

    vertex v = vertex();

    v.addLabel("Testing");

    REQUIRE(v.hasLabel("Testing"));
}

TEST_CASE("test_label_constructors")
{
    vertex * v = new vertex("Testing1");
    REQUIRE(v->hasLabel("Testing1"));
    delete v;

    std::vector<std::string> labels = {"Testing1", "Testing2"};
    v = new vertex(labels);

    REQUIRE(v->hasLabel("Testing1"));
    REQUIRE(v->hasLabel("Testing2"));

    delete v;
}

TEST_CASE ("test_remove_vertex_label")
{
    vertex v = vertex();

    v.addLabel("Testing");
    
    REQUIRE(v.hasLabel("Testing"));

    REQUIRE(v.removeLabel("Testing"));

    REQUIRE_FALSE(v.hasLabel("Testing"));
}

TEST_CASE ("test_remove_false_when_no_labels")
{
    vertex v = vertex();

    REQUIRE_FALSE(v.removeLabel("Testing"));
}

TEST_CASE ("test_remove_non_existant_label")
{
    vertex v = vertex();

    v.addLabel("Testing");
    
    REQUIRE(v.hasLabel("Testing"));

    REQUIRE_FALSE(v.removeLabel("Schmesting"));
}

TEST_CASE("test_get_labels")
{

    vertex v = vertex();

    v.addLabel("Testing");

    REQUIRE(v.getLabels()[0] == "Testing");
}

TEST_CASE("test_get_labels_as_string")
{

    vertex v = vertex();

    v.addLabel("Testing");
    v.addLabel("Testing2");
    
    std::cout << v.getLabelsAsString();
    REQUIRE(v.getLabelsAsString() == "[Testing, Testing2, ]");
}

TEST_CASE("test_get_id")
{
    vertex v = vertex(10);

    REQUIRE(v.getID() == 10);
}


