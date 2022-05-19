#include "triangulation.h"

namespace dt{

    Triangulation::Triangulation(Point a, Point b, Point c) {
        Vertex v1 = add_point(a);
        Vertex v2 = add_point(b);
        Vertex v3 = add_point(c);
        Face f = add_triangle(v1, v2, v3);
        add_line(f, v1, v2);
        add_line(f, v1, v3);
        add_line(f, v3, v2);
    }

    Face Triangulation::find_triangle(Point point) {
        for(auto face:faces){
            if(math::is_point_in_triangle(*face, point)) return face;
        }
        return nullptr;
    }

    Vertex Triangulation::add_point(Point point) {
        Vertex v = std::make_shared<Point>(point);
        vertices.push_back(v);
        return v;
    }

    Face Triangulation::add_triangle(const Vertex& a, const Vertex& b, const Vertex& c) {
        Face face = std::make_shared<Triangle>(a, b, c);
        faces.push_back(face);
        return face;
    }


    Edge Triangulation::add_line(const Face& face, const Vertex& a, const Vertex& b) {
        Edge e = find_line(a, b);
        if(e != nullptr){
            e->add_triangle(face);
            return e;
        }
        Edge edge = std::make_shared<Line>(a, b);
        edge->add_triangle(face);
        edges.push_back(edge);
        return edge;
    }

    Edge Triangulation::find_line(const Vertex &a, const Vertex &b) {
        for(Edge edge:edges){
            if(edge->contains(a) && edge->contains(b)){
                return edge;
            }
        }
        return nullptr;
    }

    void Triangulation::remove_line(const Edge& edge) {
        for(std::size_t i = 0; i < edges.size(); i++){
            if(edges[i] == edge){
                edges.erase(edges.begin() + i);
                return;
            }
        }
    }

    void Triangulation::remove_triangle(const Face &face) {
        for(std::size_t i = 0; i < faces.size(); i++){
            if(faces[i] == face){
                faces.erase(faces.begin() + i);
                return;
            }
        }
    }

    Triangulation::Triangulation()=default;
}