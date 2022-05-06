#pragma once
#include "../data/point.h"
#include "../data/area.h"
#include "../data/line.h"
#include "kd_set.h"

namespace tree_2d{
    using point::Point;
    using area::Area;
    using line::Line;
    using QueryRegion = Area;
    struct KdValue{
        Point point;
        Area area;
        Set point_set;
        Line line;
        QueryRegion query_region;
        KdValue();
        KdValue(const Point &point, const Area &area, const Set &pointSet, const Line &line,
                const QueryRegion &queryRegion);
        bool operator==(const KdValue& node);
        bool operator!=(const KdValue& node);
        bool operator>(const KdValue& node);
        bool operator<(const KdValue& node);
        bool operator>=(const KdValue& node);
        bool operator<=(const KdValue& node);

    };

    KdValue::KdValue(const Point &point, const Area &area, const Set &pointSet, const Line &line,
                     const QueryRegion &queryRegion) : point(point), area(area), point_set(pointSet), line(line),
                                                     query_region(queryRegion) {}

    KdValue::KdValue() = default;
    bool KdValue::operator==(const KdValue &node) {
        return false;
    }

    bool KdValue::operator!=(const KdValue &node) {
        return !(*this == node);
    }

    bool KdValue::operator>(const KdValue &node) {
        return false;
    }

    bool KdValue::operator<(const KdValue &node) {
        return !(*this >= node);
    }

    bool KdValue::operator>=(const KdValue &node) {
        return false;
    }

    bool KdValue::operator<=(const KdValue &node) {
        return !(*this > node);
    }



}
