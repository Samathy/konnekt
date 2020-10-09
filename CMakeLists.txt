cmake_minimum_required(VERSION 3.18)

project(konnekt)

add_definitions("--std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup(TARGETS)

find_package(Catch2 REQUIRED)
find_package(jsoncpp REQUIRED)

enable_testing()

add_executable(konnekt source/konnekt.cpp)
add_executable(tests source/test/test_main.cpp source/test/test_vertex.cpp source/test/test_graph.cpp source/test/test_edge.cpp)

target_link_libraries(konnekt ${CONAN_LIBS})
target_link_libraries(konnekt jsoncpp)

target_link_libraries(tests Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(tests)

