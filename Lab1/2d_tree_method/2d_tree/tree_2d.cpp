#include "tree_2d.h"

#include <utility>

namespace tree_2d {
    using namespace tree;
    using namespace nc;

    Set Tree2D::search_in_node(const NodePtr &node, const QueryRegion &region) {
        if (node == nullptr || node->value.is_leaf()) return {};
        node->value.query_region = region;
        QueryRegion first = std::make_shared<Area>(node->left->value.area.intersection(*region)),
                second = std::make_shared<Area>(node->right->value.area.intersection(*region));
        if (first->is_empty() && second->is_empty()) return {};
        if (!first->is_empty() && second->is_empty()) {
            return search_in_node(node->left, first);
        }
        if (first->is_empty() && !second->is_empty()) {
            return search_in_node(node->right, second);
        }
        Set res;
        if (region->contains(node->value.point)) {
            res.push_back(node->value.point);
        }
        Set left = search_in_node(node->left, first);
        res.insert(res.end(), left.begin(), left.end());
        Set right = search_in_node(node->right, second);
        res.insert(res.end(), right.begin(), right.end());

        return res;
    }

    Set Tree2D::search(const QueryRegion &region) {
        if (region->is_empty()) return {};
        return search_in_node(root, region);
    }

    Tree2D::Tree2D(Set points) {
        if (points.empty()) {
            throw std::invalid_argument{"There must be points count > 0"};
        }
        Area area{Point{DoubleConverter::INF_MINUS, DoubleConverter::INF_MINUS},
                  Point{DoubleConverter::INF_PLUS, DoubleConverter::INF_PLUS}};

        root = create_tree(points, area);
    }

    Tree2D::NodePtr Tree2D::create_tree(Set &points, Area area, bool vertical) {
        if (points.empty()) {
            return std::make_shared<Node>(Value2D{points, area});
        }
        std::size_t index = get_middle_point_index(points, vertical);
        Point point = points[index];
        Line line = get_line(point, area, vertical);
        Value2D value{points, area, point, line};
        NodePtr node = std::make_shared<Node>(value);
        Set first_set = get_first_set(points, index), second_set = get_second_set(points, index);
        Area first_area = get_first_area(area, point, vertical), second_area = get_second_area(area, point, vertical);
        node->left = create_tree(first_set, first_area, !vertical);
        node->right = create_tree(second_set, second_area, !vertical);
        return node;
    }

    Area Tree2D::get_first_area(Area &area, const Point &point, bool vertical) {
        return vertical
               ? Area{area.point1, Point{point.x, area.point2.y}}
               : Area{area.point1, Point{area.point2.x, point.y}};
    }

    Area Tree2D::get_second_area(Area &area, const Point &point, bool vertical) {
        return vertical
               ? Area{Point{point.x, area.point1.y}, area.point2}
               : Area{Point{area.point1.x, point.y}, area.point2};
    }

    Set Tree2D::get_first_set(Set &points, std::size_t index) {
        Set res;
        for (std::size_t i = 0; i < index; i++)
            res.push_back(points[i]);
        return std::move(res);
    }

    Set Tree2D::get_second_set(Set &points, std::size_t index) {
        Set res;
        for (std::size_t i = index + 1; i < points.size(); i++)
            res.push_back(points[i]);
        return std::move(res);
    }

    std::size_t Tree2D::get_middle_index(Set &points, bool vertical) {
        std::sort(points.begin(), points.end(), [vertical](const Point &one, const Point &two) {
            return vertical ? two.x > one.x : two.y > one.y;
        });

        return points.size() / 2;
    }

    std::size_t Tree2D::get_middle_point_index(Set &points, bool vertical) {
        std::size_t middle = get_middle_index(points, vertical);
        if (points.size() % 2 == 0) {
            return vertical
                   ? points[middle - 1].x < points[middle].x ? middle - 1 : middle
                   : points[middle - 1].y < points[middle].y ? middle - 1 : middle;
        }
        return middle;
    }

    Line Tree2D::get_line(const Point &point, Area area, bool vertical) {
        return vertical
               ? Line{Point{point.x, area.point1.y}, Point{point.x, area.point2.y}}
               : Line{Point{area.point1.x, point.y}, Point{area.point2.x, point.y}};
    }

}