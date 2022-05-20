#pragma once
#include <iostream>
#include <cmath>

namespace point {
    template<typename T>
    class Point2D {
    public:
        T x;
        T y;

        explicit Point2D(T x = T(), T y = T());

        template<typename V>
        friend std::ostream &operator<<(std::ostream &out, const Point2D<V> &point);
        bool operator==(const Point2D<T>&point);
    };

    template<typename T>
    class LabelPoint2D : public Point2D<T> {
    public:
        std::string label;

        explicit LabelPoint2D(T x = T(), T y = T(), std::string label = "");
    };
}
namespace point {

    template<typename T>
    LabelPoint2D<T>::LabelPoint2D(T x, T y, std::string label):Point2D<T>(x, y), label(std::move(label)) {}

    template<typename T>
    Point2D<T>::Point2D(T x, T y):x(x), y(y) {}

    template<typename V>
    std::ostream &operator<<(std::ostream &out, const Point2D<V> &point) {
        out << "{" << point.x << ", " << point.y
            << "}";
        return out;
    }

    template<typename T>
    bool Point2D<T>::operator==(const Point2D<T> &point) {
        return std::fabs(x - point.x)<=0.0000000001f && std::fabs(y - point.y)<=0.0000000001f;
    }

}