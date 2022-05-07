#pragma once
#include <memory>
#include <vector>
#include "../data/point.h"
#include "../data/area.h"
#include "../data/line.h"

namespace tree_2d{
    using Point = point::LabelPoint2D<double>;
    using Line = line::Line2D<double>;
    using Area = area::Area2D<double>;
    using Set = std::vector<Point>;
    using QueryRegion = std::shared_ptr<Area>;

    class Value2D{
    public:
        Set point_set;
        Area area;
        Point point;
        Line line;
        QueryRegion query_region;

        Value2D();

        Value2D(Set point_set, const Area &area, Point point = Point(), const Line &line = Line(),
                QueryRegion query_region = nullptr);
        bool is_leaf() const;
        bool operator==(const Value2D& node);
        bool operator!=(const Value2D& node);
        bool operator>(const Value2D& node);
        bool operator<(const Value2D& node);
        bool operator>=(const Value2D& node);
        bool operator<=(const Value2D& node);
    };
    std::ostream& operator<<(std::ostream& out, const Value2D& value);
}
