#include "math_functions.h"

namespace math{

    bool is_point_in_circle(Triangle triangle, Point d) {
        mymatrix::SquareMatrix matrix{{
            {triangle.a.x, triangle.a.y, triangle.a.x*triangle.a.x + triangle.a.y*triangle.a.y, 1},
            {triangle.b.x, triangle.b.y, triangle.b.x*triangle.b.x + triangle.b.y*triangle.b.y, 1},
            {triangle.c.x, triangle.c.y, triangle.c.x*triangle.c.x + triangle.c.y*triangle.c.y, 1},
            {d.x,          d.y,          d.x*d.x + d.y*d.y,                                     1}
        }};
        return matrix.det() < 0;
    }

    bool is_point_in_triangle(Triangle triangle, Point d) {
        double first = (triangle.a.x - d.x)*(triangle.b.y - triangle.a.y)
                - (triangle.b.x - triangle.a.x)*(triangle.a.y - d.y);
        double second = (triangle.b.x - d.x)*(triangle.c.y - triangle.b.y)
                - (triangle.c.x - triangle.b.x)*(triangle.b.y - d.y);
        double third = (triangle.c.x - d.x)*(triangle.a.y - triangle.c.y)
                - (triangle.a.x - triangle.c.x)*(triangle.c.y - d.y);
        return sign(first) == sign(second) && sign(second) == sign(third) && sign(first) != 0;
    }

    int sign(double number) {
        if(number > 0) return 1;
        if(number < 0) return -1;
        return 0;
    }
}
