#include "delaunay_triangulation.h"

#include <utility>

namespace dt{
    using namespace point;
    DelaunayTriangulation::DelaunayTriangulation(Set points) : points(std::move(points)){
        triangulation = Triangulation(remove_random_point(), remove_random_point(), remove_random_point());
    }

    void DelaunayTriangulation::add_point(Point point) {
        std::cout << point << std::endl;
        Face face = triangulation.find_triangle(point);
        if(face == nullptr){
            Vertex p = triangulation.add_point(point);
            return;
        }
        std::cout <<"\n\nAdd point" << std::endl;
        std::cout << "face: " << *(face->a) << " " << *(face->b) << " " << *(face->c) << std::endl;
        Vertex p = triangulation.add_point(point);
        Face abp = triangulation.add_triangle(face->a, face->b, p);
        Face acp = triangulation.add_triangle(face->a, face->c, p);
        Face cbp = triangulation.add_triangle(face->c, face->b, p);
        Edge ab = triangulation.find_line(face->a, face->b);
        ab->change_triangle(face, abp);
        Edge ac = triangulation.find_line(face->a, face->c);
        ac->change_triangle(face, acp);
        Edge cb = triangulation.find_line(face->c, face->b);
        cb->change_triangle(face, cbp);
        Edge ap = triangulation.add_line(abp, face->a, p);
        ap->add_triangle(acp);
        Edge bp = triangulation.add_line(abp, face->b, p);
        bp->add_triangle(cbp);
        Edge cp = triangulation.add_line(acp, face->c, p);
        cp->add_triangle(cbp);
        std::stack<pa::Pair<Face, Edge>> stack;
        stack.push(pa::Pair<Face, Edge>(abp, ab));
        stack.push(pa::Pair<Face, Edge>(acp, ac));
        stack.push(pa::Pair<Face, Edge>(cbp, cb));
        run(stack);
        triangulation.remove_triangle(face);
    }


    Point DelaunayTriangulation::remove_random_point() {
        std::size_t index = rand()%points.size();
        Point point = points[index];
        points.erase(points.begin()+index);
        return point;
    }

    bool DelaunayTriangulation::add_next() {
        if(points.empty()) return false;
        add_point(remove_random_point());
        return true;
    }

    void DelaunayTriangulation::run(std::stack<pa::Pair<Face, Edge>> &stack) {
        while (!stack.empty()){
            auto f = stack.top();
            stack.pop();
            Face opp = f.two->get_opposed_triangle(f.one);
            if(opp == nullptr) continue;
            std::cout << "Opp: " << *(opp->a) << " " << *(opp->b) << " " << *(opp->c) << std::endl;
            Vertex d = opp->get_other(f.two->start, f.two->end);
            std::cout << "D: " << *d << std::endl;
            if(math::is_point_in_circle(*(f.one), *d)){
                std::cout << "\nD in circle!" << std::endl;
                triangulation.remove_line(f.two);
                triangulation.remove_triangle(f.one);
                triangulation.remove_triangle(opp);
                Vertex p = f.one->get_other(f.two->start, f.two->end);
                std::cout << "P: " << *p << std::endl;
                Face apd = triangulation.add_triangle(p, d, f.two->start);
                Edge ap = triangulation.find_line(p, f.two->start);
                ap->change_triangle(f.one, apd);
                Edge ad = triangulation.find_line(d, f.two->start);
                ad->change_triangle(opp, apd);
                stack.push(pa::Pair<Face, Edge>(apd, ad));

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
