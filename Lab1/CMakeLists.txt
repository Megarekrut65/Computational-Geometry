cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp 2d_tree/binary_tree.h 2d_tree/kd_value.h data/point.h data/area.h data/line.h 2d_tree/binary_node.h 2d_tree/tree_2d.h 2d_tree/kd_set.h)
