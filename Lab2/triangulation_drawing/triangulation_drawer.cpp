#include "triangulation_drawer.h"

#include <utility>

namespace drawer {
    const unsigned TriangulationDrawer::HEIGHT = 800;
    const unsigned TriangulationDrawer::WIDTH = 800;

    void TriangulationDrawer::run() {
        while (window.isOpen()) {
            events();
            window.clear(DrawingColors::BACKGROUND);
            draw();
            window.display();
        }
    }

    void TriangulationDrawer::events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (delaunay_triangulation.add_next()) {
                        converter.convert();
                        continue;
                    }
                    if (points_to_insert.empty()) continue;
                    delaunay_triangulation.add_point(af::remove_random_item(points_to_insert));
                    converter.convert();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                    need_circle = !need_circle;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    screenshot.take();
                }
            }

        }
    }

    void TriangulationDrawer::draw() {
        if (need_circle) {
            for (const auto &circle: converter.get_circles()) {
                window.draw(circle);
            }
        }
        for (const auto &line: converter.get_lines()) {
            sf::Vertex l[] = {line[0], line[1]};
            window.draw(l, 2, sf::Lines);
        }
        for (const auto &point: converter.get_points()) {
            window.draw(point);
        }
    }

    TriangulationDrawer::TriangulationDrawer(const dt::Set &initial_points, dt::Set points, int zoom)
            : delaunay_triangulation(initial_points), points_to_insert(std::move(points)),
              screenshot(ScreenshotTaker("../screenshots", window)) {
        converter = TriangulationDrawingConverter(&delaunay_triangulation, Normalizer(HEIGHT, WIDTH, zoom));
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Delaunay Triangulation", sf::Style::Default);
        converter.convert();
    }


}
