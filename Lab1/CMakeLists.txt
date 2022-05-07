cmake_minimum_required(VERSION 3.21)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 2d_tree_method/main.cpp 2d_tree_method/binary_tree/binary_tree.h 2d_tree_method/2d_tree/value_2d.h 2d_tree_method/data/point.h 2d_tree_method/data/area.h 2d_tree_method/data/line.h 2d_tree_method/binary_tree/binary_node.h 2d_tree_method/2d_tree/tree_2d.h 2d_tree_method/2d_tree/value_2d.cpp 2d_tree_method/2d_tree/tree_2d.cpp 2d_tree_method/points_reader.h 2d_tree_method/menu/menu.cpp 2d_tree_method/menu/menu.h 2d_tree_method/number_converter.h)
