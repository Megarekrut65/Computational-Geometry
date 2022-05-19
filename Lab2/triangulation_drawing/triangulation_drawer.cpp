#include "triangulation_drawer.h"

#include <utility>

namespace drawer{
    const unsigned TriangulationDrawer::HEIGHT = 800;
    const unsigned TriangulationDrawer::WIDTH = 800;
    const sf::Color TriangulationDrawer::BACKGROUND = sf::Color(245,222,179);
    const sf::Color TriangulationDrawer::LINE = sf::Color::Black;
    const sf::Color TriangulationDrawer::POINT = sf::Color::Red;
    const sf::Color TriangulationDrawer::CIRCLE = sf::Color(46,139,87, 120);
    void TriangulationDrawer::run() {
        while (window.isOpen()){
            events();
            window.clear(BACKGROUND);
            draw();
            window.display();
        }
    }

    void TriangulationDrawer::events() {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    if(delaunay_triangulation.add_next()){
                        create_shapes_triangulation();
                    }else{
                        if(points_to_insert.empty()) continue;
                        std::size_t index = rand() % points_to_insert.size();
                        dt::Point point = points_to_insert[index];
                        points_to_insert.erase(points_to_insert.begin() + index);
                        delaunay_triangulation.add_point(point);
                        create_shapes_triangulation();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                    need_circle = !need_circle;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    window.close();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    screenshot.take();
                }
            }

        }
    }

    void TriangulationDrawer::draw() {
        if(need_circle){
            for(const auto& circle:circles){
                window.draw(circle);
            }
        }
        for(const auto& line:lines){
            sf::Vertex l[]= {line[0], line[1]};
            window.draw(l, 2, sf::Lines);
        }
        for(const auto& point:points){
            window.draw(point);
        }
    }

    TriangulationDrawer::TriangulationDrawer(const dt::Set &initial_points, dt::Set points, int zoom)
    : delaunay_triangulation(initial_points), points_to_insert(std::move(points)), zoom(zoom),
        screenshot(ScreenshotTaker("../screenshots", window)) {
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Delaunay Triangulation", sf::Style::Default);
        create_shapes_triangulation();
    }

    void TriangulationDrawer::create_shapes_triangulation() {
        circles.clear();
        lines.clear();
        points.clear();
        auto vertices = delaunay_triangulation.get_vertices();
        for(const auto& vertex:vertices){
            sf::CircleShape point(3.0f);
            point.setFillColor(POINT);
            point.setPosition(normalize_x(vertex->x) - point.getRadius(),
                              normalize_y(vertex->y) - point.getRadius());
            points.push_back(point);
        }
        auto edges = delaunay_triangulation.get_edges();
        for(const auto& edge:edges){
            lines.push_back({sf::Vertex(sf::Vector2f(normalize_x(edge->start->x), normalize_y(edge->start->y)), LINE),
                             sf::Vertex(sf::Vector2f(normalize_x(edge->end->x), normalize_y(edge->end->y)), LINE)});
        }
        auto faces = delaunay_triangulation.get_faces();
        for(const auto& face:faces){
            dt::Line ab(face->a, face->b), bc(face->b, face->c);
            dt::Line bi_ab = math::bisection(ab), bi_bc = math::bisection(bc);
            std::shared_ptr<dt::Point> center = math::intersect(bi_ab, bi_bc);
            if(center == nullptr) continue;
            float length = math::get_length(*(face->a), *center);
            sf::CircleShape circle(zoom*length);
            circle.setFillColor(sf::Color(0,0,0,0));
            circle.setPosition(normalize_x(center->x) - circle.getRadius(),
                               normalize_y(center->y) - circle.getRadius());
            circle.setOutlineThickness(1.0f);
            circle.setOutlineColor(CIRCLE);
            circles.push_back(circle);
        }
    }

    float TriangulationDrawer::normalize_x(float x) {
        return x*zoom + WIDTH/2.0f;
    }

    float TriangulationDrawer::normalize_y(float y) {
        return -y*zoom + HEIGHT/2.0f;
    }

}
