#pragma once

#include <algorithm>
#include "../binary_tree/binary_tree.h"
#include "value_2d.h"

namespace tree_2d{

    class Tree2D:public tree::BinaryTree<Value2D>{
    private:
        static std::size_t get_middle_point_index(Set& points, bool vertical = true);
        static Line get_line(const Point& point, Area area, bool vertical= true);
        static std::size_t get_middle_index(Set& points, bool vertical= true);
        static Set get_first_set(Set& points, std::size_t index);
        static Set get_second_set(Set& points, std::size_t index);
        static Area get_first_area(Area& area, const Point& point, bool vertical = true);
        static Area get_second_area(Area& area, const Point& point, bool vertical = true);
        NodePtr create_tree(Set& points,Area area, bool vertical = true);
    public:
        explicit Tree2D(Set points);
        Value2D search(const QueryRegion& region);
    };
    using Tree = Tree2D;
}