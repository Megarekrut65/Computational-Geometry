#pragma once
#include <vector>
#include "../data/point.h"

namespace tree_2d{
    using Set = std::vector<point::Point>;
    std::ostream &operator<<(std::ostream &out, const Set& set){
        for(auto item:set){
            out << item << " ";
        }
        return out;
    }
}