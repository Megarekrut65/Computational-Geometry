#pragma once

#include "point.h"
#include "triangle.h"

namespace line {
    template<typename T>
    class Line2D {
    public:
        std::shared_ptr<point::Point2D<T>> start;
        std::shared_ptr<point::Point2D<T>> end;
        std::shared_ptr<tri::Triangle2D<T>> triangle1;
        std::shared_ptr<tri::Triangle2D<T>> triangle2;

        explicit Line2D(const std::shared_ptr<point::Point2D<T>> &start = nullptr,
                        const std::shared_ptr<point::Point2D<T>> &anEnd = nullptr);

        bool contains(std::shared_ptr<point::Point2D<T>> point);

        void add_triangle(std::shared_ptr<tri::Triangle2D<T>> triangle);

        void change_triangle(std::shared_ptr<tri::Triangle2D<T>> old_one, std::shared_ptr<tri::Triangle2D<T>> new_one);

        std::shared_ptr<tri::Triangle2D<T>> get_opposed_triangle(std::shared_ptr<tri::Triangle2D<T>> triangle);

        bool is_border() const;
    };

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Line2D<T> &line);
}
namespace line {
    template<typename T>
    Line2D<T>::Line2D(const std::shared_ptr<point::Point2D<T>> &start, const std::shared_ptr<point::Point2D<T>> &anEnd)
            :triangle1(nullptr), triangle2(nullptr), start(start), end(anEnd) {}

    template<typename T>
    bool Line2D<T>::contains(std::shared_ptr<point::Point2D<T>> point) {
        return point == start || point == end;
    }

    template<typename T>
    void Line2D<T>::add_triangle(std::shared_ptr<tri::Triangle2D<T>> triangle) {
        change_triangle(nullptr, triangle);
    }

    template<typename T>
    void Line2D<T>::change_triangle(std::shared_ptr<tri::Triangle2D<T>> old_one,
                                    std::shared_ptr<tri::Triangle2D<T>> new_one) {
        if (triangle1 == old_one) {
            triangle1 = new_one;
            return;
        }
        if (triangle2 == old_one) {
            triangle2 = new_one;
        }
    }

    template<typename T>
    std::shared_ptr<tri::Triangle2D<T>> Line2D<T>::get_opposed_triangle(std::shared_ptr<tri::Triangle2D<T>> triangle) {
        if (triangle1 == triangle) {
            return triangle2;
        }
        if (triangle2 == triangle) {
            return triangle1;
        }
        return nullptr;
    }

    template<typename T>
    bool Line2D<T>::is_border() const {
        return triangle1 == nullptr || triangle2 == nullptr;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &out, const Line2D<T> &line) {
        out << *(line.start) << "->" << *(line.end);
        return out;
    }
}