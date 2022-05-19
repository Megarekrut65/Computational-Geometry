#pragma once
#include <SFML/Graphics.hpp>
#include "../delaunay_triangulation/delaunay_triangulation.h"

namespace drawer{
    class TriangulationDrawer {
    private:
        dt::DelaunayTriangulation delaunayTriangulation;
        sf::RenderWindow window;
    public:
        void run();
    };
}


