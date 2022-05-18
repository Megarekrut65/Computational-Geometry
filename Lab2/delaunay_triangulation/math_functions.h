#pragma once
#include "data/triangle.h"
#include "data/matrix/square_matrix.h"

namespace math{
    using Point = point::Point2D<double>;
    using Triangle = tri::Triangle2D<double>;
    bool is_point_in_circle(Triangle triangle, Point d);
    bool is_point_in_triangle(Triangle triangle, Point d);
    int sign(double number);
}