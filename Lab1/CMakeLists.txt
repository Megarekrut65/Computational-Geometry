cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp binary_tree/binary_tree.h 2d_tree/value_2d.h data/point.h data/area.h data/line.h binary_tree/binary_node.h 2d_tree/tree_2d.h 2d_tree/value_2d.cpp 2d_tree/tree_2d.cpp)
