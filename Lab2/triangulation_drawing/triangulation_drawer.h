#pragma once
#include <SFML/Graphics.hpp>
#include "../delaunay_triangulation/delaunay_triangulation.h"
#include "screenshot_taker.h"
#include <vector>

namespace drawer{
    class TriangulationDrawer {
    private:
        static const unsigned HEIGHT;
        static const unsigned WIDTH;
        static const sf::Color BACKGROUND;
        static const sf::Color LINE;
        static const sf::Color POINT;
        static const sf::Color CIRCLE;
        dt::DelaunayTriangulation delaunay_triangulation;
        sf::RenderWindow window;
        std::vector<sf::CircleShape> circles;
        std::vector<sf::CircleShape> points;
        std::vector<std::vector<sf::Vertex>> lines;
        bool need_circle = true;
        dt::Set points_to_insert;
        int zoom;
        ScreenshotTaker screenshot;
        void events();
        void draw();
        void create_shapes_triangulation();
        float normalize_x(float x);
        float normalize_y(float y);
    public:
        TriangulationDrawer(const dt::Set& initial_points, dt::Set  points, int zoom = 1);
        void run();
    };
}


