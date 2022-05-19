#pragma once
#include "data/point.h"
#include "data/matrix/square_matrix.h"
#include "data/triangle.h"
#include "math_functions.h"
#include <vector>
#include <stack>
#include "data/pair.h"
#include "data/triangulation.h"

namespace dt{
    using Set = std::vector<Point>;
    class DelaunayTriangulation {
    private:
        Set points;
        Triangulation triangulation;
        void add_point(Point point);
        Point remove_random_point();
        void run(std::stack<pa::Pair<Face, Edge>>& stack);
    public:
        explicit DelaunayTriangulation(Set points);
        void add_next();
    };
}


