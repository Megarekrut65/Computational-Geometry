#include "delaunay_triangulation.h"

#include <utility>

namespace dt {
    using namespace point;

    DelaunayTriangulation::DelaunayTriangulation(Set points) : points(std::move(points)) {
        if (this->points.size() < 3) {
            throw std::invalid_argument{"There must be 3 and more points for triangulation!"};
        }
        triangulation = Triangulation(remove_random_point(), remove_random_point(), remove_random_point());
    }

    void DelaunayTriangulation::add_point(Point point) {
        Face face = triangulation.find_triangle(point);
        Vertex p = triangulation.add_point(point);
        if (face == nullptr) {
            add_point_outside(p);
            return;
        }
        add_point_inside(p, face);
    }

    void DelaunayTriangulation::add_point_inside(const Vertex &p, const Face &face) {
        //create triangles with vertex p
        Face abp = triangulation.add_triangle(face->a, face->b, p);
        Face acp = triangulation.add_triangle(face->a, face->c, p);
        Face cbp = triangulation.add_triangle(face->c, face->b, p);
        //replace old triangles with new ones
        Edge ab = triangulation.find_line(face->a, face->b);
        ab->change_triangle(face, abp);
        Edge ac = triangulation.find_line(face->a, face->c);
        ac->change_triangle(face, acp);
        Edge cb = triangulation.find_line(face->c, face->b);
        cb->change_triangle(face, cbp);
        //add new lines between p and other vertices of triangle that contains p
        Edge ap = triangulation.add_line(abp, face->a, p);
        ap->add_triangle(acp);
        Edge bp = triangulation.add_line(abp, face->b, p);
        bp->add_triangle(cbp);
        Edge cp = triangulation.add_line(acp, face->c, p);
        cp->add_triangle(cbp);
        //add new triangles to stack and check delaunay condition
        std::stack<pa::Pair<Face, Edge>> stack;
        stack.push(pa::Pair<Face, Edge>(abp, ab));
        stack.push(pa::Pair<Face, Edge>(acp, ac));
        stack.push(pa::Pair<Face, Edge>(cbp, cb));
        check_condition(stack);
        //in any case, this triangle will not exist
        triangulation.remove_triangle(face);
    }

    void DelaunayTriangulation::check_condition(std::stack<pa::Pair<Face, Edge>> &stack) {
        while (!stack.empty()) {
            auto f = stack.top();
            stack.pop();
            Face opp = f.two->get_opposed_triangle(f.one);
            if (opp == nullptr) continue;
            Vertex d = opp->get_other(f.two->start, f.two->end);
            if (math::is_point_in_circle(*(f.one), *d)) {
                //remove old triangles
                triangulation.remove_line(f.two);
                triangulation.remove_triangle(f.one);
                triangulation.remove_triangle(opp);
                Vertex p = f.one->get_other(f.two->start, f.two->end);
                //create new triangle
                Face apd = triangulation.add_triangle(p, d, f.two->start);
                Edge ap = triangulation.find_line(p, f.two->start);
                ap->change_triangle(f.one, apd);
                Edge ad = triangulation.find_line(d, f.two->start);
                ad->change_triangle(opp, apd);
                stack.push(pa::Pair<Face, Edge>(apd, ad));
                //create new triangle
                Face bpd = triangulation.add_triangle(p, d, f.two->end);
                Edge bp = triangulation.find_line(p, f.two->end);
                bp->change_triangle(f.one, bpd);
                Edge bd = triangulation.find_line(d, f.two->end);
                bd->change_triangle(opp, bpd);
                stack.push(pa::Pair<Face, Edge>(bpd, bd));

                Edge dp = triangulation.add_line(apd, d, p);
                dp->add_triangle(bpd);
            }
        }
    }

    void DelaunayTriangulation::add_point_outside(const Vertex &p) {
        Face min = nullptr;
        float min_len = 0;
        for (const auto &edge: triangulation.get_edges()) {
            if (!edge->is_border()) return;
            Point point = math::get_point_line_perpendicular(*edge, *p);
            if (math::segment_contains_point(*edge, point)) {
                float len = math::get_length(point, *p);
                if (min == nullptr || len < min_len) {
                    min = std::make_shared<Triangle>(p, edge->start, edge->end);
                    min_len = len;
                }
            }
        }
        if (min != nullptr) {
            Face face = triangulation.add_triangle(min->a, min->b, min->c);
            triangulation.add_line(face, min->a, min->b);
            triangulation.add_line(face, min->a, min->c);
            Edge edge = triangulation.find_line(min->b, min->c);
            edge->add_triangle(face);
        }
    }

    Point DelaunayTriangulation::remove_random_point() {
        return af::remove_random_item(points);
    }

    bool DelaunayTriangulation::add_next() {
        if (points.empty()) return false;
        add_point(remove_random_point());
        return true;
    }

    std::vector<Vertex> DelaunayTriangulation::get_vertices() {
        return triangulation.get_vertices();
    }

    std::vector<Edge> DelaunayTriangulation::get_edges() {
        return triangulation.get_edges();
    }

    std::vector<Face> DelaunayTriangulation::get_faces() {
        return triangulation.get_faces();
    }

}
