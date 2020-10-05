cmake_minimum_required(VERSION 3.18)

project(konnekt)

add_definitions("--std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(konnekt source/konnekt.cpp)
target_link_libraries(konnekt ${CONAN_LIBS})

