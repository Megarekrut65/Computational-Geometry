#pragma once
#include "data/point.h"
#include "data/matrix/square_matrix.h"
#include "data/triangle.h"
#include <vector>

namespace dt{
    using Point = point::Point2D<double>;
    using Triangle = tri::Triangle2D<double>;
    using Set = std::vector<Point>;
    class DelaunayTriangulation {
    private:
        Set points;
    public:
        explicit DelaunayTriangulation(Set points);
    };
}


