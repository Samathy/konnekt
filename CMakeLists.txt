cmake_minimum_required(VERSION 3.18)

project(konnekt)

add_definitions("--std=c++17")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup()

find_package(Catch2 REQUIRED)

enable_testing()

add_executable(konnekt source/konnekt.cpp)
add_executable(tests source/test/test_main.cpp)
target_link_libraries(konnekt ${CONAN_LIBS})

target_link_libraries(tests Catch2::Catch2 ${CONAN_LIBS})

include(CTest)
include(Catch)
catch_discover_tests(tests)

