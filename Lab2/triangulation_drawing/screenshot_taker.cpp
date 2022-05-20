#include "screenshot_taker.h"

#include <utility>

namespace drawer {

    ScreenshotTaker::ScreenshotTaker(std::string pathToFolder, const sf::RenderWindow &window) : path_to_folder(
            std::move(
                    pathToFolder)), window(window), count(0) {}

    bool ScreenshotTaker::take() {
        sf::Texture texture;
        texture.create(window.getSize().x, window.getSize().y);
        texture.update(window);
        return texture.copyToImage().saveToFile(path_to_folder + "/screenshot" + std::to_string(++count) + ".png");
    }
}