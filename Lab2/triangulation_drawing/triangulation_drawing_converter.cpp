#include "triangulation_drawing_converter.h"

namespace drawer {

    const std::vector<sf::CircleShape> &TriangulationDrawingConverter::get_circles() const {
        return circles;
    }

    const std::vector<sf::CircleShape> &TriangulationDrawingConverter::get_points() const {
        return points;
    }

    const std::vector<std::vector<sf::Vertex>> &TriangulationDrawingConverter::get_lines() const {
        return lines;
    }

    void TriangulationDrawingConverter::convert() {
        convert_circles();
        convert_lines();
        convert_points();
    }

    TriangulationDrawingConverter::TriangulationDrawingConverter(dt::DelaunayTriangulation *triangulation,
                                                                 const Normalizer &norm) : triangulation(triangulation),
                                                                                           norm(norm) {}

    void TriangulationDrawingConverter::convert_circles() {
        circles.clear();
        auto faces = triangulation->get_faces();
        for (const auto &face: faces) {
            dt::Point center = math::get_circle_center_around_triangle(*face);
            float length = math::get_length(*(face->a), center);
            sf::CircleShape circle(norm.normalize_length(length));
            circle.setFillColor(sf::Color(0, 0, 0, 0));
            circle.setPosition(norm.normalize_x(center.x) - circle.getRadius(),
                               norm.normalize_y(center.y) - circle.getRadius());
            circle.setOutlineThickness(1.0f);
            circle.setOutlineColor(DrawingColors::CIRCLE);
            circles.push_back(circle);
        }
    }

    void TriangulationDrawingConverter::convert_points() {
        points.clear();
        auto vertices = triangulation->get_vertices();
        for (const auto &vertex: vertices) {
            sf::CircleShape point(3.0f);
            point.setFillColor(DrawingColors::POINT);
            point.setPosition(norm.normalize_x(vertex->x) - point.getRadius(),
                              norm.normalize_y(vertex->y) - point.getRadius());
            points.push_back(point);
        }
        points[points.size() - 1].setFillColor(DrawingColors::SELECT);
    }

    void TriangulationDrawingConverter::convert_lines() {
        lines.clear();
        auto edges = triangulation->get_edges();
        for (const auto &edge: edges) {
            lines.push_back(
                    {sf::Vertex(sf::Vector2f(norm.normalize_x(edge->start->x), norm.normalize_y(edge->start->y)),
                                DrawingColors::LINE),
                     sf::Vertex(sf::Vector2f(norm.normalize_x(edge->end->x), norm.normalize_y(edge->end->y)),
                                DrawingColors::LINE)});
        }
    }

    TriangulationDrawingConverter::TriangulationDrawingConverter() : triangulation(nullptr) {}
}
