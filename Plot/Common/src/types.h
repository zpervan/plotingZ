#ifndef PLOTINGZ_TYPES_H
#define PLOTINGZ_TYPES_H

#include <map>
#include <SFML/Graphics/Color.hpp>

static const std::map<std::size_t, sf::Color> mapped_colors{
        {0, sf::Color::Black},
        {1, sf::Color::Red},
        {2, sf::Color::Green},
        {3, sf::Color::Blue},
        {4, sf::Color::Yellow},
        {5, sf::Color::Magenta},
        {6, sf::Color::Cyan}};

enum class PlotType {
    Unknown = 0,
    ScatterPlot,
    LinePlot
};

#endif //PLOTINGZ_TYPES_H
