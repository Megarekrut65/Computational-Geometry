#include <iostream>
#include "delaunay_triangulation/math_functions.h"
#include "delaunay_triangulation/delaunay_triangulation.h"
#include <SFML/Graphics.hpp>


int main() {
//    bool is = math::is_point_in_triangle(math::Triangle(math::Point(-4,0), math::Point(0,4), math::Point(4,0)),
//                                         math::Point(-3,1));
//    if(is) std::cout << "IS!" << std::endl;
//    else std::cout << "No!" << std::endl;
//    dt::DelaunayTriangulation triangulation({math::Point(-4,0), math::Point(0,0), math::Point(0,4),
//                                             math::Point(-4,4),math::Point(2,1)});
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window", sf::Style::Default);
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color(150, 50, 250));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                shape.setPosition(50, 50);
        }
        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }

    return 0;
}
