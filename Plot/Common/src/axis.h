#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "Plot/Common/src/config.h"
#include "Plot/Common/src/plotting_data.h"
#include <SFML/Graphics.hpp>
#include <cstddef>

/// @todo: At origin of axis, render 0 only once!
/// @todo: Scale axis values text when values are more than one character
/// @todo: Grid?
/// @todo: Consider smoothing axis lines and a grayish color

class Axis {
public:
    explicit Axis(PlottingData &plotting_data) : plotting_data_{plotting_data} {}

    ~Axis() = default;

    /// Sets the values (markers) on the X-axis. The highest marker value should be the max value of the input data.
    /// @param size Number of markers
    void SetXAxis(std::size_t size);

    /// Sets the values (markers) on the Y-axis. The highest marker value should be the max value of the input data.
    /// @param size Number of markers
    void SetYAxis(std::size_t size);

    /// Creates the axis shapes
    void CreateAxis();

private:

    sf::RectangleShape CreateXAxis();

    sf::RectangleShape CreateYAxis();

    std::vector<sf::RectangleShape> CreateAxisMarkers(std::size_t axis_size, bool is_x_axis);

    std::size_t ReserveAxisShapeSpace() const;

    std::vector<sf::Text> AddAxisMarkerValues(size_t marker_count, bool is_x_axis);

    sf::Text CreateMarkerValueText(std::size_t value, bool is_x_axis, float offset_percentage);

    PlottingData &plotting_data_;
    std::size_t x_axis_size_{0};
    std::size_t y_axis_size_{0};
};


#endif //PLOTINGZ_AXIS_H
