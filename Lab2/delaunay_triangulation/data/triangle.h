#pragma once
#include "point.h"
#include <memory>

namespace tri{
    template<typename T>
    class Triangle2D{
        void print_point(std::ostream& out, std::shared_ptr<point::Point2D<T>> point) const;
    public:
        std::shared_ptr<point::Point2D<T>> a;
        std::shared_ptr<point::Point2D<T>> b;
        std::shared_ptr<point::Point2D<T>> c;

        Triangle2D(const std::shared_ptr<point::Point2D<T>> &a,
                   const std::shared_ptr<point::Point2D<T>> &b,
                   const std::shared_ptr<point::Point2D<T>> &c);
        std::shared_ptr<point::Point2D<T>> get_other(std::shared_ptr<point::Point2D<T>> p1,
            std::shared_ptr<point::Point2D<T>> p2);
        template<typename V>
        friend std::ostream& operator<<(std::ostream& out, const Triangle2D<V>& triangle2D);
    };

}
namespace tri{

    template<typename T>
    Triangle2D<T>::Triangle2D(const std::shared_ptr<point::Point2D<T>> &a,
                              const std::shared_ptr<point::Point2D<T>> &b,
                              const std::shared_ptr<point::Point2D<T>> &c)
    :a(a), b(b), c(c) {}

    template<typename T>
    std::shared_ptr<point::Point2D<T>>
    Triangle2D<T>::get_other(std::shared_ptr<point::Point2D<T>> p1, std::shared_ptr<point::Point2D<T>> p2) {
        if(p1 == a){
            if(p2 == b){
                return c;
            }
            if(p2 == c){
                return b;
            }
            return nullptr;
        }
        if(p1 == b){
            if(p2 == a){
                return c;
            }
            if(p2 == c){
                return a;
            }
            return nullptr;
        }
        if(p1 == c){
            if(p2 == b){
                return a;
            }
            if(p2 == a){
                return b;
            }
        }
        return nullptr;
    }

    template<typename T>
    void Triangle2D<T>::print_point(std::ostream &out, std::shared_ptr<point::Point2D<T>> point)const {
        if(point == nullptr){
            out << "NULL";
            return;
        }
        out << *point;
    }
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Triangle2D<T>& triangle2D){
        out << "<";
        triangle2D.print_point(out, triangle2D.a);
        out << ", ";
        triangle2D.print_point(out, triangle2D.b);
        out << ", ";
        triangle2D.print_point(out, triangle2D.c);
        out << ">";
        return out;
    }
}