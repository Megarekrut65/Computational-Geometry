#include <iostream>
#include "delaunay_triangulation/math_functions.h"

int main() {
    bool is = math::is_point_in_triangle(math::Triangle(math::Point(-4,0), math::Point(0,4), math::Point(4,0)),
                                         math::Point(-3,1));
    if(is) std::cout << "IS!" << std::endl;
    else std::cout << "No!" << std::endl;
    return 0;
}
