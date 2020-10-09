/** Contains ingest functions to create a graph from input.
 */

#include <string>
#include <fstream>
#include <iostream>
#include <memory>


#include "json/json.h"


#include "graph.h"

/** Parse a json input file and return a parsed Json::Value object
 */
Json::Value parseJson(std::string filename)
{
    Json::Value root;

    std::ifstream f;
    f.open(filename);

    Json::CharReaderBuilder builder;

    Json::String errs;

    if (!parseFromStream(builder, f, &root, & errs))
    {
        std::cout << errs;
        throw "Could not parse json input";
    }

    return root;
}


/** Parse a json description of our graph and turn it into an in-memory
 * representation.
 *
 * Returns a unique_ptr to a new graph object.
 */
std::unique_ptr<graph> ingest_json(std::string filename)
{
    std::unique_ptr<graph> ret(new graph());

    Json::Value root = parseJson(filename);

    Json::Value vertices = root["verticies"];
    Json::Value edges = root["edges"];

    if (vertices)
    {
        int i;
        for ( i = 0; i < vertices.size(); i++)
        {
            if (!vertices[i]["label"].asString().empty())
            {
                ret->createVertex()->addLabel(vertices[i]["label"].asString());
                
            }
            else
                ret->createVertex();
        }

        std::cout << "Created " << i << " verticies."<< std::endl;
    }

    if (edges)
    {
        int i;
        for ( i = 0; i < edges.size(); i++)
        {
            std::vector<std::shared_ptr<vertex>> v1(ret->findVertex(edges[i]["v1"].asString()));
            std::vector<std::shared_ptr<vertex>> v2(ret->findVertex(edges[i]["v2"].asString()));

            if (v1.size() == 0 || v2.size() == 0 )
            {
                std::cout << "Cannot create edge. Could not find vertexs matching one or both labels: "<< edges[i]["v1"].asString() << ", " << edges[i]["v2"].asString();
            }
           
            //If you've labeled multiple vertices with the same label
            //and you're trying to add edges between each pair, thats not going to work.
            //I'd be simple to change, but I'm sticking with this for now.
            ret->createEdge(v1[0], v2[0]);
        }
        std::cout << "Created " << i << " edges."<< std::endl;
    }

    std::cout << "Created graph" << std::endl;

    return ret;
}
