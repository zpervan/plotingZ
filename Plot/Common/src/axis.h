#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "Plot/Common/src/config.h"
#include <SFML/Graphics.hpp>
#include <cstddef>

class Axis {
public:
    /// Sets the number of markers on the X-axis
    /// @param size Number of markers
    void SetXAxis(const std::size_t size);

    /// Sets the number of markers on the Y-axis
    /// @param size Number of markers
    void SetYAxis(const std::size_t size);

    /// Fills the vector of rectangle shape with the XY axis shape
    /// @return X and Y axis shape
    /// @todo: A better name? CreateAxis perhaps?
    const std::vector<sf::RectangleShape> DrawAxis();

    std::vector<sf::RectangleShape> GetAxisShapes();

protected:
    sf::RectangleShape CreateXAxis();

    sf::RectangleShape CreateYAxis();

    const std::vector<sf::RectangleShape> CreateAxisMarkers(std::size_t axis_size, bool is_x_axis);

    std::vector<sf::RectangleShape> axis_shape_;
    std::size_t x_axis_size_{0};
    std::size_t y_axis_size_{0};
};


#endif //PLOTINGZ_AXIS_H
