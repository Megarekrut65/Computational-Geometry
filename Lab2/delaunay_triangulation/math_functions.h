#pragma once
#include "data/triangle.h"
#include "data/matrix/square_matrix.h"
#include "data/line.h"
#include <cmath>

namespace math{
    using Point = point::Point2D<float>;
    using Triangle = tri::Triangle2D<float>;
    using Line = line::Line2D<float>;
    bool is_point_in_circle(const Triangle &triangle, Point d);
    bool is_point_in_triangle(const Triangle& triangle, Point d);
    int sign(float number);
    float get_length(Point start, Point end);
    float get_area(const Triangle& triangle);
    std::shared_ptr<Point> intersect(const Line& a, const Line& b);
    Line bisection(const Line& line);
}