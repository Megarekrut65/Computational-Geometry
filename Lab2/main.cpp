#include <iostream>
#include "delaunay_triangulation/delaunay_triangulation.h"

int main() {
    bool is = dt::DelaunayTriangulation()
        .is_in_circle(dt::Triangle(dt::Point(-4, 0), dt::Point(0, 4), dt::Point(4, 0)), dt::Point(-3,3));
    if(is) std::cout << "Is" << std::endl;
    else std::cout <<"No!" << std::endl;

    return 0;
}
