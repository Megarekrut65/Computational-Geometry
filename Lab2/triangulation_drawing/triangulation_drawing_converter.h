#pragma once
#include "../delaunay_triangulation/delaunay_triangulation.h"
#include "drawing_colors.h"
#include "normalizer.h"
#include <SFML/Graphics.hpp>

namespace drawer{
    class TriangulationDrawingConverter {
    private:
        dt::DelaunayTriangulation* triangulation;
        std::vector<sf::CircleShape> circles;
        std::vector<sf::CircleShape> points;
        std::vector<std::vector<sf::Vertex>> lines;
        Normalizer norm;
        void convert_circles();
        void convert_points();
        void convert_lines();
    public:
        TriangulationDrawingConverter();

        TriangulationDrawingConverter(dt::DelaunayTriangulation *triangulation, const Normalizer &norm);

        void convert();

        const std::vector<sf::CircleShape> &get_circles() const;

        const std::vector<sf::CircleShape> &get_points() const;

        const std::vector<std::vector<sf::Vertex>> &get_lines() const;
    };
}


