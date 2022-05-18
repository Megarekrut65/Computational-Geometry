#include "delaunay_triangulation.h"

namespace dt{
    using namespace mymatrix;

    bool DelaunayTriangulation::is_in_circle(Triangle triangle, Point d) {
        mymatrix::SquareMatrix matrix{{
            {triangle.a.x, triangle.a.y, triangle.a.x*triangle.a.x + triangle.a.y*triangle.a.y, 1},
            {triangle.b.x, triangle.b.y, triangle.b.x*triangle.b.x + triangle.b.y*triangle.b.y, 1},
            {triangle.c.x, triangle.c.y, triangle.c.x*triangle.c.x + triangle.c.y*triangle.c.y, 1},
            {d.x,          d.y,          d.x*d.x + d.y*d.y,                                     1}
        }};
        return matrix.det() < 0;
    }
}
