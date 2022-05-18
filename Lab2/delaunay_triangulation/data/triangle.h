#pragma once
#include "point.h"

namespace tri{
    template<typename T>
    class Triangle2D{
    public:
        point::Point2D<T> a;
        point::Point2D<T> b;
        point::Point2D<T> c;

        Triangle2D(const point::Point2D<T> &a, const point::Point2D<T> &b, const point::Point2D<T> &c);
    };
}
namespace tri{
    template<typename T>
    Triangle2D<T>::Triangle2D(const point::Point2D<T> &a, const point::Point2D<T> &b, const point::Point2D<T> &c)
    :a(a), b(b), c(c) {}
}