#ifndef PLOTINGZ_CONFIG_H
#define PLOTINGZ_CONFIG_H
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <zconf.h>

using AxisData = std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>>;

namespace Config {
    static constexpr uint WINDOW_WIDTH{640};
    static constexpr uint WINDOW_HEIGHT{480};
    static constexpr uint FONT_SIZE{16};
    static constexpr float MARKER_LENGTH{10.f};
    static constexpr float LINE_WIDTH{2.0f};
    static constexpr float EDGE_OFFSET{80.f};

    static const sf::Vector2f REFERENCE_POINT{WINDOW_WIDTH * 0.0625, WINDOW_HEIGHT * 0.916666667};
    static const sf::Vector2f X_AXIS_REFERENCE_POINT{REFERENCE_POINT.x - MARKER_LENGTH / 2,
                                                     REFERENCE_POINT.y + FONT_SIZE / 2};
    static const sf::Vector2f Y_AXIS_REFERENCE_POINT{REFERENCE_POINT.x - MARKER_LENGTH * 2,
                                                     REFERENCE_POINT.y - FONT_SIZE / 2};

    static const sf::Vector2f MARKER_DIMENSION{MARKER_LENGTH, LINE_WIDTH};
    static const sf::Vector2f X_AXIS_DIMENSION{WINDOW_WIDTH - EDGE_OFFSET, LINE_WIDTH};
    static const sf::Vector2f Y_AXIS_DIMENSION{LINE_WIDTH, WINDOW_HEIGHT - EDGE_OFFSET};
    static sf::Font FONT{};
}
/// @todo: Create a function which initializes the font object?
namespace Global {
    static const void SetFont() {
        sf::Font font;
        font.loadFromFile("Plot/Fonts/JetBrainsMono-Regular.ttf");
        Config::FONT = font;
    }
}
#endif //PLOTINGZ_CONFIG_H
