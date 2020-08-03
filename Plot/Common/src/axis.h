#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "Plot/Common/src/config.h"
#include <SFML/Graphics.hpp>
#include <cstddef>

/// @todo: Add values on XY axis
/// @todo: Grid?
/// @todo: Consider smoothing axis lines and a grayish color

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
    void DrawAxis();

    const std::vector<sf::RectangleShape> GetAxisShapes() const;

    const std::vector<sf::Text> GetAxisMarkerValues() const;

protected:
    const sf::RectangleShape CreateXAxis();

    const sf::RectangleShape CreateYAxis();

    const std::vector<sf::RectangleShape> CreateAxisMarkers(std::size_t axis_size, bool is_x_axis);

    const std::size_t ReserveAxisShapeSpace() const;

    const std::vector<sf::Text> AddAxisMarkerValues(const size_t marker_count, bool is_x_axis);

    sf::Text CreateMarkerValueText(const std::size_t value, bool is_x_axis, const float offset_percentage);

    std::vector<sf::RectangleShape> axis_shapes_;
    std::vector<sf::Text> axis_marker_values_;
    std::size_t x_axis_size_{0};
    std::size_t y_axis_size_{0};
};


#endif //PLOTINGZ_AXIS_H
