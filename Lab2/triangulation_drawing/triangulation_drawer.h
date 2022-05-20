#pragma once

#include <SFML/Graphics.hpp>
#include "../delaunay_triangulation/delaunay_triangulation.h"
#include "../additional_functions/array_functions.h"
#include "screenshot_taker.h"
#include "triangulation_drawing_converter.h"
#include <vector>

namespace drawer {
    class TriangulationDrawer {
    private:
        static const unsigned HEIGHT;
        static const unsigned WIDTH;

        dt::DelaunayTriangulation delaunay_triangulation;
        sf::RenderWindow window;
        ScreenshotTaker screenshot;
        TriangulationDrawingConverter converter;
        dt::Set points_to_insert;
        bool need_circle = true;

        void events();

        void draw();

    public:
        TriangulationDrawer(const dt::Set &initial_points, dt::Set points, int zoom = 1);

        void run();
    };
}


