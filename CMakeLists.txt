cmake_minimum_required(VERSION 3.10)
project(PositCppLibrary)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(posit include/posit.hpp include/posit.tpp)

add_executable(example examples/example.cpp)
target_link_libraries(example posit)
