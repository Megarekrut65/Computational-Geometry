#include "value_2d.h"


namespace tree_2d{
    using namespace point;
    using namespace line;
    using namespace area;

    Value2D::Value2D() = default;
    bool Value2D::operator==(const Value2D &node) {
        return false;
    }

    bool Value2D::operator!=(const Value2D &node) {
        return !(*this == node);
    }

    bool Value2D::operator>(const Value2D &node) {
        return false;
    }

    bool Value2D::operator<(const Value2D &node) {
        return !(*this >= node);
    }

    bool Value2D::operator>=(const Value2D &node) {
        return false;
    }

    bool Value2D::operator<=(const Value2D &node) {
        return !(*this > node);
    }

    Value2D::Value2D(Set point_set, const Area &area, Point point, const Line &line,
                     QueryRegion query_region) : point_set(std::move(point_set)), point(std::move(point)), line(line), area(area),
                                                 query_region(std::move(query_region)) {}

    bool Value2D::is_leaf() const{
        return point_set.empty();
    }
    std::ostream &operator<<(std::ostream& out, const Set& set){
        for(const auto& item:set)
            out << item << " ";
        return out;
    }
    std::ostream& operator<<(std::ostream& out, const Value2D& value){
        if(value.is_leaf()){
            out <<"leaf";
        }else{
            out << "{ "<<value.point.label << ": "<< value.point << ", point_set: "
            << value.point_set << ", line: " << value.line;
        }

        return out;
    }
}
