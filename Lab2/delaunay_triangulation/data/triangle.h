#pragma once
#include "point.h"
#include <memory>

namespace tri{
    template<typename T>
    class Triangle2D{
    public:
        std::shared_ptr<point::Point2D<T>> a;
        std::shared_ptr<point::Point2D<T>> b;
        std::shared_ptr<point::Point2D<T>> c;

        Triangle2D(const std::shared_ptr<point::Point2D<T>> &a,
                   const std::shared_ptr<point::Point2D<T>> &b,
                   const std::shared_ptr<point::Point2D<T>> &c);
        std::shared_ptr<point::Point2D<T>> get_other(std::shared_ptr<point::Point2D<T>> p1,
            std::shared_ptr<point::Point2D<T>> p2);
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
}