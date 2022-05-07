#pragma once

#include <algorithm>
#include "../binary_tree/binary_tree.h"
#include "value_2d.h"
#include "../number_converter.h"

namespace tree_2d {

    class Tree2D : public tree::BinaryTree<Value2D> {
    private:
        /**
         *
         * @param points - set of points
         * @param vertical - true if cut is vertical else false
         * @return index of point of cutting
         */
        static std::size_t get_middle_point_index(Set &points, bool vertical = true);
        /**
         *
         * @param point of cutting
         * @param area to cut
         * @param vertical - true if cut is vertical else false
         * @return line that cut area by point
         */
        static Line get_line(const Point &point, Area area, bool vertical = true);
        /**
         * Sorts set
         * @param points - set of points
         * @param vertical - true if cut is vertical else false
         * @return index of center point in set
         */
        static std::size_t get_middle_index(Set &points, bool vertical = true);
        /**
         *
         * @param points - set of points
         * @param index of cutting point
         * @return first part of set cutting by point
         */
        static Set get_first_set(Set &points, std::size_t index);
        /**
         *
         * @param points - set of points
         * @param index of cutting point
         * @return second part of set cutting by point
         */
        static Set get_second_set(Set &points, std::size_t index);
        /**
         *
         * @param area to cut
         * @param point of cutting
         * @param vertical - true if cut is vertical else false
         * @return first part of area cutting by point
         */
        static Area get_first_area(Area &area, const Point &point, bool vertical = true);
        /**
         *
         * @param area to cut
         * @param point of cutting
         * @param vertical - true if cut is vertical else false
         * @return second part of area cutting by point
         */
        static Area get_second_area(Area &area, const Point &point, bool vertical = true);
        /**
         *
         * @param node of searching
         * @param region of searching
         * @return found points
         */
        Set search_in_node(const NodePtr &node, const QueryRegion &region);
        /**
         * Creates tree from points set
         * @param points - set of points
         * @param area - area of points
         * @param vertical - true if cut is vertical else false
         * @return created node
         */
        NodePtr create_tree(Set &points, Area area, bool vertical = true);

    public:
        /**
         * Creates tree from points set
         * @param points - set of points
         */
        explicit Tree2D(Set points);
        /**
         * Searches points in query region
         * @param region of searching
         * @return found points
         */
        Set search(const QueryRegion &region);
    };

    using Tree = Tree2D;
}