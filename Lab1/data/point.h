#pragma once

namespace point{

    template<typename T>
    class Point2D{
    public:
        T x;
        T y;
        explicit Point2D(T x=T(), T y=T());
    };
    using Point = Point2D<double>;
    template<typename T>
    std::ostream &operator<<(std::ostream& out, const Point2D<T>& point);

    template<typename T>
    Point2D<T>::Point2D(T x, T y):x(x), y(y) {}

    template<typename T>
    std::ostream &operator<<(std::ostream& out, const Point2D<T>& point){
        out << "{" << point.x << ", " << point.y << "}";
        return out;
    }

}
