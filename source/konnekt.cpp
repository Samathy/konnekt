#include "ingest.h"

int main()
{
    std::unique_ptr<graph>  g;
    g = ingest_json("example1.json");
}
