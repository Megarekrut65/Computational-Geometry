#pragma once
#include "data/point.h"
#include "data/matrix/square_matrix.h"
#include "data/triangle.h"

namespace dt{
    using Point = point::Point2D<double>;
    using Triangle = tri::Triangle2D<double>;

    class DelaunayTriangulation {
    public:
        bool is_in_circle(Triangle triangle, Point d);
    };
}


