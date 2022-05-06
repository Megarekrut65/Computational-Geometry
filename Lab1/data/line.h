#pragma once
#include "point.h"

namespace line{
    template<typename T>
    class Line2D{
    public:
        point::Point2D<T> start;
        point::Point2D<T> end;
        explicit Line2D(const point::Point2D<T> &start = point::Point2D<T>(),
                const point::Point2D<T> &anEnd = point::Point2D<T>());
    };

    template<typename T>
    Line2D<T>::Line2D(const point::Point2D<T> &start, const point::Point2D<T> &anEnd):start(start), end(anEnd) {
    }
    using Line = Line2D<double>;
}