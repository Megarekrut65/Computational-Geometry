cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab2 main.cpp delaunay_triangulation/data/point.h delaunay_triangulation/data/matrix/my_matrix.h delaunay_triangulation/data/matrix/square_matrix.h delaunay_triangulation/data/matrix/square_matrix.cpp delaunay_triangulation/delaunay_triangulation.cpp delaunay_triangulation/delaunay_triangulation.h delaunay_triangulation/data/triangle.h)
