#pragma once
#include <limits>
#include <sstream>

namespace point{
    template<typename T>
    class Point2D{
    private:
        std::string value_to_string(T value) const;
    public:
        static const T INF_PLUS;
        static const T INF_MINUS;
        T x;
        T y;

        explicit Point2D(T x=T(), T y=T());
        template<typename V>
        friend std::ostream &operator<<(std::ostream& out, const Point2D<V>& point);
    };

    template<typename T>
    class LabelPoint2D: public Point2D<T>{
    public:
        std::string label;
        explicit LabelPoint2D(T x = T(), T y = T(), std::string label = "");
    };
}
namespace point{
    template<typename T>
    const T Point2D<T>::INF_PLUS = std::numeric_limits<T>::max();
    template<typename T>
    const T Point2D<T>::INF_MINUS = std::numeric_limits<T>::min();

    template<typename T>
    LabelPoint2D<T>::LabelPoint2D(T x, T y, std::string label):Point2D<T>(x,y), label(std::move(label)) {}
    template<typename T>
    Point2D<T>::Point2D(T x, T y):x(x), y(y) {}
    template<typename T>
    std::string Point2D<T>::value_to_string(T value) const{
        if(value == INF_PLUS) return "+INF";
        if(value == INF_MINUS) return "-INF";
        std::stringstream stream;
        stream << value;
        return stream.str();
    }
    template<typename V>
    std::ostream &operator<<(std::ostream& out, const Point2D<V>& point){
        out << "{" << point.value_to_string(point.x) << ", " << point.value_to_string(point.y) << "}";
        return out;
    }
}