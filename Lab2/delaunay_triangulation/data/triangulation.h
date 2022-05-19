#pragma once
#include "triangle.h"
#include "point.h"
#include "line.h"
#include <vector>
#include <memory>
#include "../math_functions.h"

namespace dt{
    using Point = point::Point2D<float>;
    using Line = line::Line2D<float>;
    using Triangle = tri::Triangle2D<float>;
    using Vertex = std::shared_ptr<Point>;
    using Face = std::shared_ptr<Triangle>;
    using Edge = std::shared_ptr<Line>;
    class Triangulation {
    private:
        std::vector<Vertex> vertices;
    public:
        const std::vector<Vertex> &get_vertices() const;

        const std::vector<Face> &get_faces() const;

        const std::vector<Edge> &get_edges() const;

    private:
        std::vector<Face> faces;
        std::vector<Edge> edges;
    public:
        Triangulation();
        Triangulation(Point a, Point b, Point c);
        Face find_triangle(Point point);
        Vertex add_point(Point point);
        Face add_triangle(const Vertex& a, const Vertex& b, const Vertex& c);
        Edge add_line(const Face& face, const Vertex& a, const Vertex& b);
        Edge find_line(const Vertex& a, const Vertex& b);
        void remove_line(const Edge& edge);
        void remove_triangle(const Face& face);
    };
}


