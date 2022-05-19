#include "math_functions.h"

namespace math{

    bool is_point_in_circle(const Triangle& triangle, Point d) {
        mymatrix::SquareMatrix matrix{{
            {triangle.a->x, triangle.a->y, triangle.a->x*triangle.a->x + triangle.a->y*triangle.a->y, 1},
            {triangle.b->x, triangle.b->y, triangle.b->x*triangle.b->x + triangle.b->y*triangle.b->y, 1},
            {triangle.c->x, triangle.c->y, triangle.c->x*triangle.c->x + triangle.c->y*triangle.c->y, 1},
            {d.x,          d.y,          d.x*d.x + d.y*d.y,                                     1}
        }};
        return matrix.det() > 0;
    }

    bool is_point_in_triangle(const Triangle& triangle, Point d) {
        float first = (triangle.a->x - d.x)*(triangle.b->y - triangle.a->y)
                - (triangle.b->x - triangle.a->x)*(triangle.a->y - d.y);
        float second = (triangle.b->x - d.x)*(triangle.c->y - triangle.b->y)
                - (triangle.c->x - triangle.b->x)*(triangle.b->y - d.y);
        float third = (triangle.c->x - d.x)*(triangle.a->y - triangle.c->y)
                - (triangle.a->x - triangle.c->x)*(triangle.c->y - d.y);
        return sign(first) == sign(second) && sign(second) == sign(third) && sign(first) != 0;
    }

    int sign(float number) {
        if(number > 0) return 1;
        if(number < 0) return -1;
        return 0;
    }

    float get_length(Point start, Point end) {
        return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    }

    float get_area(const Triangle &triangle) {
        float ab = get_length(*(triangle.a),*(triangle.b)),
                bc = get_length(*(triangle.c),*(triangle.b)),
                ac= get_length(*(triangle.a),*(triangle.c));
        float p = (ab + bc + ac)/2.0f;
        return sqrt(p*(p-ab)*(p-ac)*(p-bc));
    }

    std::shared_ptr<Point> intersect(const Line &a, const Line &b) {
        float x1 = a.start->x, y1 = a.start->y, x2 = a.end->x, y2 = a.end->y,
                x3 = b.start->x, y3 = b.start->y, x4 = b.end->x, y4 = b.end->y;
        float a1 = y1 - y2;
        float b1 = x2 - x1;
        float c1 = x1 * y2 - x2 * y1;
        float a2 = y3 - y4;
        float b2 = x4 - x3;
        float c2 = x3 * y4 - x4 * y3;
        if ((a1 / a2) == (b1 / b2)) return nullptr;
        float det = a1 * b2 - a2 * b1;
        float x = (b1 * c2 - b2 * c1) / det;
        float y = (a2 * c1 - a1 * c2) / det;
        return std::make_shared<Point>(x,y);
    }

    Line bisection(const Line &line) {//y = m*x + b
        Point middle((line.start->x + line.end->x)/2.0f, (line.start->y + line.end->y)/2.0f);
        float slope = (line.end->y - line.start->y)/(line.end->x - line.start->x);
        float m = -1.0f*(1.0f/slope);
        float b = middle.y - m * middle.x;
        float x = 2.0f*middle.x + 1.0f;
        float y = m*x + b;
        Point next(x,y);
        return math::Line(std::make_shared<Point>(middle), std::make_shared<Point>(next));
    }
}
