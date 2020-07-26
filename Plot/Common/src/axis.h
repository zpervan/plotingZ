#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "include/SFML/Graphics.hpp"
#include <cstddef>

class Axis {
public:
    void SetXAxisSize(const std::size_t size);

    void SetYAxisSize(const std::size_t size);

    void DrawAxis();

protected:
    std::vector<sf::RectangleShape> axis_shape_;
    std::size_t x_axis_size_{0};
    std::size_t y_axis_size_{0};
};


#endif //PLOTINGZ_AXIS_H
