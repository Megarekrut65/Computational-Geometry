#pragma once

#include "data/point.h"
#include <vector>
#include <fstream>

namespace pr {
    template<typename T>
    std::istream &operator>>(std::istream &in, std::vector<point::LabelPoint2D<T>> &points);

    template<typename T>
    std::vector<point::LabelPoint2D<T>> read_points(const std::string &path);
}
namespace pr {
    using namespace point;

    template<typename T>
    std::istream &operator>>(std::istream &in, std::vector<point::LabelPoint2D<T>> &points) {
        while (!in.eof()) {
            LabelPoint2D<T> point;
            in >> point.label >> point.x >> point.y;
            if (!point.label.empty()) points.push_back(point);
        }
        return in;
    }

    template<typename T>
    std::vector<point::LabelPoint2D<T>> read_points(const std::string &path) {
        std::ifstream in{path};
        if (!in.is_open()) {
            in.close();
            return {};
        }
        std::vector<point::LabelPoint2D<T>> res;
        in >> res;
        in.close();
        return std::move(res);
    }
}

