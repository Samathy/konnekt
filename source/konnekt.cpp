#include <iostream>
#include "ingest.h"

int main(int argc, char ** argv)
{
    std::unique_ptr<graph> g;
    if ( argc >= 1 )
    {
        std::cout << "Ingesting graph from: " << argv[1] << std::endl;
        g = ingest_json(argv[1]);
    }
    else
        std::cout << "Ingesting graph from exmaple1.json";
        g = ingest_json("example1.json");

    std::cout << g->getDot();
}
