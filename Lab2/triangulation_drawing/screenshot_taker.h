#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace drawer{
    class ScreenshotTaker {
    private:
        int count;
        std::string path_to_folder;
        const sf::RenderWindow& window;
    public:
        ScreenshotTaker(std::string pathToFolder, const sf::RenderWindow &window);
        bool take();
    };
}

