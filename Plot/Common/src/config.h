#ifndef PLOTINGZ_CONFIG_H
#define PLOTINGZ_CONFIG_H

#include <SFML/System/Vector2.hpp>

#include <zconf.h>

namespace Config {
    static constexpr uint WINDOW_WIDTH{640};
    static constexpr uint WINDOW_HEIGHT{480};
    static constexpr float LINE_WIDTH{2.0f};
    static constexpr float EDGE_OFFSET{80.f};

    static const sf::Vector2f REFERENCE_POINT{WINDOW_WIDTH * 0.0625, WINDOW_HEIGHT * 0.916666667};
    static const sf::Vector2f MARKER_DIMENSION{10.f, LINE_WIDTH};
    /// @todo: Find a better way to calculate the X and Y axis. Needed for scaling w.r.t. window dimension
    static const sf::Vector2f X_AXIS_DIMENSION{WINDOW_WIDTH - EDGE_OFFSET, LINE_WIDTH};
    static const sf::Vector2f Y_AXIS_DIMENSION{LINE_WIDTH, WINDOW_HEIGHT - EDGE_OFFSET};
}

#endif //PLOTINGZ_CONFIG_H
