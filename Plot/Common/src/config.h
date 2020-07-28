#ifndef PLOTINGZ_CONFIG_H
#define PLOTINGZ_CONFIG_H

#include <SFML/System/Vector2.hpp>

#include <zconf.h>

namespace Config {
    static constexpr uint WindowWidth{640};
    static constexpr uint WindowHeight{480};
    static const sf::Vector2f ReferencePoint{WindowWidth * 0.03125, WindowHeight * 0.958333333};
}

#endif //PLOTINGZ_CONFIG_H
