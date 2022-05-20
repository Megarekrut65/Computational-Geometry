#pragma once

#include "data/point.h"
#include "data/triangle.h"
#include "../additional_functions/math_functions.h"
#include <vector>
#include <stack>
#include "data/pair.h"
#include "data/triangulation.h"
#include "../additional_functions/array_functions.h"

namespace dt {
    using Set = std::vector<Point>;

    class DelaunayTriangulation {
    private:
        Set points;
        Triangulation triangulation;

        Point remove_random_point();

        void check_condition(std::stack<pa::Pair<Face, Edge>> &stack);

        void add_point_inside(const Vertex &p, const Face &face);

        void add_point_outside(const Vertex &p);

    public:
        explicit DelaunayTriangulation(Set points);

        bool add_next();

        void add_point(Point point);

        std::vector<Vertex> get_vertices();

        std::vector<Edge> get_edges();

        std::vector<Face> get_faces();
    };
}


