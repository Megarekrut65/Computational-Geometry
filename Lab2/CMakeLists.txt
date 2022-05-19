cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "E:/Clion/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

add_executable(Lab2 main.cpp delaunay_triangulation/data/point.h delaunay_triangulation/data/matrix/my_matrix.h delaunay_triangulation/data/matrix/square_matrix.h delaunay_triangulation/data/matrix/square_matrix.cpp delaunay_triangulation/delaunay_triangulation.cpp delaunay_triangulation/delaunay_triangulation.h delaunay_triangulation/data/triangle.h delaunay_triangulation/math_functions.cpp delaunay_triangulation/math_functions.h delaunay_triangulation/data/triangulation.cpp delaunay_triangulation/data/triangulation.h delaunay_triangulation/data/line.h delaunay_triangulation/data/pair.h triangulation_drawing/triangulation_drawer.cpp triangulation_drawing/triangulation_drawer.h)

target_link_libraries(Lab2 sfml-graphics)
