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
        Point remove_random_point();
        void run(std::stack<pa::Pair<Face, Edge>>& stack);
    public:
        explicit DelaunayTriangulation(Set points);
        bool add_next();
        void add_point(Point point);
        std::vector<Vertex> get_vertices();
        std::vector<Edge> get_edges();
        std::vector<Face> get_faces();
    };
}


