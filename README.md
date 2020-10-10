Konnekt
=======

Konnect is a C++17 application built and tested with CMake and GCC on Linux.

clang-format is used with it's default settings for formatting.

Libraries used are listed in the conanfile.

Documentation is available in the docs directory.

## Building the executable

### Prerequisits
 * [Conan](https://conan.io)
 * [CMake](https://cmake.org)

### Prep
 1) cd build
 2) conan install .. --build=jsoncpp
 3) cmake ..

### Build

 1) cd build
 2) cmake --build .

## Testing
Testing is implemented with [Catch2](https://github.com/catchorg/catch2)

 1) cd build
 2) cmake --build .
 3) ctest

## Documentation
Documentation is available in the docs folder.

Documentation can be generated with doxygen:
    $ doxygen Doxyfile

## Usage

    konnect [graph file]
Injest a graph and exit

    konnekt [graph file] [--shortest-path] [source node label] [destination node label]
Find the shortest path between two nodes.

    konnekt [graph file] [--dot]
Produce a dot representation of a given graph.

### Json serialisation format

Konnekt can ingest graphs in a json format that looks like the following:

```json
{
    "vertices": [
        {
            "label": "wibble"
        },
        {
            "label": "dibble"
        },
        {
            "label": ""
        }
    ],
    "edges": [
        {
            "v1": "wibble"
            "v2": "dibble"
        }
    ]
}
```

Vertices do not have to have 
