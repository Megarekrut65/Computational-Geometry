#include "math_functions.h"

namespace math{

    bool is_point_in_circle(const Triangle& triangle, Point d) {
        Point center = get_circle_center_around_triangle(triangle);
        Real radius = get_length(*(triangle.a), center);
        Real len = get_length(d, center);
        return len < radius;
//        mymatrix::SquareMatrix matrix{{
//            {triangle.a->x, triangle.a->y, triangle.a->x*triangle.a->x + triangle.a->y*triangle.a->y, 1},
//            {triangle.b->x, triangle.b->y, triangle.b->x*triangle.b->x + triangle.b->y*triangle.b->y, 1},
//            {triangle.c->x, triangle.c->y, triangle.c->x*triangle.c->x + triangle.c->y*triangle.c->y, 1},
//            {d.x,          d.y,          d.x*d.x + d.y*d.y,                                     1}
//        }};
//        return matrix.det() > 0;
    }

    bool is_point_in_triangle(const Triangle& triangle, Point d) {
        Real first = (triangle.a->x - d.x)*(triangle.b->y - triangle.a->y)
                - (triangle.b->x - triangle.a->x)*(triangle.a->y - d.y);
        Real second = (triangle.b->x - d.x)*(triangle.c->y - triangle.b->y)
                - (triangle.c->x - triangle.b->x)*(triangle.b->y - d.y);
        Real third = (triangle.c->x - d.x)*(triangle.a->y - triangle.c->y)
                - (triangle.a->x - triangle.c->x)*(triangle.c->y - d.y);
        return sign(first) == sign(second) && sign(second) == sign(third) && sign(first) != 0;
    }

    int sign(Real number) {
        if(number > 0) return 1;
        if(number < 0) return -1;
        return 0;
    }

    Real get_length(Point start, Point end) {
        return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    }

    Real get_area(const Triangle &triangle) {
        Real ab = get_length(*(triangle.a),*(triangle.b)),
                bc = get_length(*(triangle.c),*(triangle.b)),
                ac= get_length(*(triangle.a),*(triangle.c));
        Real p = (ab + bc + ac)/2;
        return sqrt(p*(p-ab)*(p-ac)*(p-bc));
    }

    std::shared_ptr<Point> intersect(const Line &a, const Line &b) {
        Real x1 = a.start->x, y1 = a.start->y, x2 = a.end->x, y2 = a.end->y,
                x3 = b.start->x, y3 = b.start->y, x4 = b.end->x, y4 = b.end->y;
        Real a1 = y1 - y2;
        Real b1 = x2 - x1;
        Real c1 = x1 * y2 - x2 * y1;
        Real a2 = y3 - y4;
        Real b2 = x4 - x3;
        Real c2 = x3 * y4 - x4 * y3;
        if ((a1 / a2) == (b1 / b2)) return nullptr;
        Real det = a1 * b2 - a2 * b1;
        Real x = (b1 * c2 - b2 * c1) / det;
        Real y = (a2 * c1 - a1 * c2) / det;
        return std::make_shared<Point>(x,y);
    }

    Line bisection(const Line &line) {//y = m*x + b
        Point middle((line.start->x + line.end->x)/2.0f, (line.start->y + line.end->y)/2.0f);
        Real slope = (line.end->y - line.start->y)/(line.end->x - line.start->x);
        Real m = -1.0f*(1.0f/slope);
        Real b = middle.y - m * middle.x;
        Real x = 2.0f*middle.x + 1.0f;
        Real y = m*x + b;
        Point next(x,y);
        return math::Line(std::make_shared<Point>(middle), std::make_shared<Point>(next));
    }

    Point get_circle_center_around_triangle(const Triangle &triangle) {
        Line ab(triangle.a, triangle.b), bc(triangle.b, triangle.c);
        Line bi_ab = math::bisection(ab), bi_bc = bisection(bc);
        std::shared_ptr<Point> center = intersect(bi_ab, bi_bc);
        if(center == nullptr){
            std::stringstream ss;
            ss<<triangle;
            throw std::invalid_argument{"Triangle " + ss.str() + " is invalid!"};
        }
        return *center;
    }
}
