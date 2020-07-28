#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "Plot/Common/src/config.h"
#include <SFML/Graphics.hpp>
#include <cstddef>

class Axis {
public:
    void SetXAxisSize(const std::size_t size);

    void SetYAxisSize(const std::size_t size);

    const std::vector<sf::RectangleShape> DrawAxis();


protected:
    sf::RectangleShape CreateXAxis();

    sf::RectangleShape CreateYAxis();

    const std::vector<sf::RectangleShape> DrawAxisMarkers(std::size_t marker_count, bool is_y_axis);

    std::vector<sf::RectangleShape> axis_shape_;
    std::size_t x_axis_size_{0};
    std::size_t y_axis_size_{0};
};


#endif //PLOTINGZ_AXIS_H
