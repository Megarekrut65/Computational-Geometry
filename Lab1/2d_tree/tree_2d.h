#pragma once

#include <algorithm>
#include "binary_tree.h"
#include "kd_value.h"

namespace tree_2d{
    using namespace tree;
    class Tree2D:public BinaryTree<KdValue>{
    public:
        Tree2D();
        explicit Tree2D(Set points);
        KdValue search(const QueryRegion& region);
    };

    Tree2D::Tree2D():BinaryTree<KdValue>() {
    }

    KdValue Tree2D::search(const QueryRegion &region) {

    }

    Tree2D::Tree2D(Set points) {
        if(points.empty()){
            throw std::invalid_argument{"There must be points count > 0"};
        }
        std::sort(points.begin(), points.end(), [](const point::Point& one, const point::Point& two){
            return two.x > one.x;
        });
        std::size_t middle = points.size()/2;
        point::Point point;
        if(points.size()%2==0){
            point = points[middle-1].x < points[middle].x?points[middle-1]:points[middle];
        }else{
            point = points[middle];
        }
        std::cout << point << std::endl;
    }

    using Tree = Tree2D;
}