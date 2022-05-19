#pragma once
#include "data/triangle.h"
#include "data/matrix/square_matrix.h"
#include "data/line.h"
#include <cmath>
#include <sstream>

namespace math{
    using Real = float;
    using Point = point::Point2D<Real>;
    using Triangle = tri::Triangle2D<Real>;
    using Line = line::Line2D<Real>;
    bool is_point_in_circle(const Triangle &triangle, Point d);
    bool is_point_in_triangle(const Triangle& triangle, Point d);
    int sign(Real number);
    Real get_length(Point start, Point end);
    Real get_area(const Triangle& triangle);
    std::shared_ptr<Point> intersect(const Line& a, const Line& b);
    Line bisection(const Line& line);
    Point get_circle_center_around_triangle(const Triangle& triangle);
}