#include "delaunay_triangulation.h"

#include <utility>

namespace dt{

    DelaunayTriangulation::DelaunayTriangulation(Set points) : points(std::move(points)){}
}
