#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "Plot/Common/src/config.h"
#include "Plot/Common/src/plotting_data.h"
#include <SFML/Graphics.hpp>
#include <cstddef>

/// @todo: Scale axis values text when values are more than one character
/// @todo: Grid?
/// @todo: Consider smoothing axis lines and a grayish color

class Axis {
public:
    explicit Axis(PlottingData *plotting_data) : plotting_data_{plotting_data} {}

    ~Axis() = default;

    Axis() = default;

    Axis(const Axis &rhs) = delete;

    Axis(Axis &&rhs) = delete;

    Axis &operator=(const Axis &rhs) = delete;

    Axis &operator=(Axis &&rhs) = delete;

    /// @brief Sets the values (markers) on the X-axis. The highest marker value should be the max value of the input data.
    /// @param [in] max_marker_value Number of markers
    void SetXAxisMaxMarkerValue(float max_marker_value);

    /// @brief Sets the values (markers) on the Y-axis. The highest marker value should be the max value of the input data.
    /// @param [in] max_marker_value Number of markers
    void SetYAxisMaxMarkerValue(float max_marker_value);

    /// @brief Creates the axis shapes
    void CreateAxis();

private:
    std::size_t CalculateAxisMarkerUpperBoundValue(float max_value);

    std::size_t CalculateAxisMarkerLowerBoundValue(float min_value);

    std::vector<sf::RectangleShape> CreateAxisShapes();

    std::size_t ReserveAxisShapeSpace() const;

    sf::RectangleShape CreateAxisShapeSkeleton(const sf::Vector2f &shape_dimension, const float angle);

    std::vector<sf::RectangleShape> CreateXAxisMarkerShapes();

    std::vector<sf::RectangleShape> CreateYAxisMarkerShapes();

    std::size_t GenerateNumberOfMarkersOnAxis(std::size_t max_marker_value);

    std::vector<sf::Text> CreateAxisMarkerValues();

    std::vector<sf::Text> AddValueToAxisMarkers(std::size_t max_marker_value, std::size_t marker_count, bool is_x_axis);

    sf::Text CreateMarkerValueText(std::size_t value, bool is_x_axis, float offset_percentage);

    PlottingData *plotting_data_{nullptr};
    std::size_t x_axis_marker_count_{0};
    std::size_t y_axis_marker_count_{0};
};


#endif //PLOTINGZ_AXIS_H
