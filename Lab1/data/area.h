#pragma once

namespace area{
    template<typename T>
    class Area2D{
    public:
        point::Point2D<T> point1;
        point::Point2D<T> point2;
        Area2D();
        Area2D(const point::Point2D<T> &point1, const point::Point2D<T> &point2);
        Area2D<T> intersection(Area2D<T> area) const;
        bool is_empty() const;
        bool contains(const point::Point2D<T>& point) const;
    };
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Area2D<T>& area);
}
namespace area{
    template<typename T>
    Area2D<T>::Area2D() = default;
    template<typename T>
    Area2D<T>::Area2D(const point::Point2D<T> &point1, const point::Point2D<T> &point2):point1(point1),
                                                                                        point2(point2) {}
    template<typename T>
    Area2D<T> Area2D<T>::intersection(Area2D<T> area) const{
        return Area2D<T>{
                point::Point2D<T>{std::max(point1.x, area.point1.x), std::max(point1.y, area.point1.y)},
                point::Point2D<T>{std::min(point2.x, area.point2.x), std::min(point2.y, area.point2.y)}};
    }
    template<typename T>
    bool Area2D<T>::is_empty() const {
        return point1.x > point2.x || point1.y > point2.y;
    }

    template<typename T>
    bool Area2D<T>::contains(const point::Point2D<T>& point) const{
        return point.x >= point1.x
            && point.x <= point2.x
            && point.y >= point1.y
            && point.y <= point2.y;
    }
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Area2D<T>& area){
        out << "[" << area.point1.x << ", " << area.point1.y
            <<"]x[" << area.point2.x << ", " << area.point2.y<<"]";
        return out;
    }
}