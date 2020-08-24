#include "Plot/Common/src/axis.h"
#include "ThirdParty/fmt/include/fmt/format.h"
#include "config.h"

#include <cmath>

void Axis::SetXAxisMaxMarkerValue(const float max_marker_value) {
    const std::size_t max_x_marker_value = CalculateAxisMarkerUpperBoundValue(max_marker_value);
    plotting_data_->SetMaxXMarkerValue(max_x_marker_value);
    x_axis_marker_count_ = GenerateNumberOfMarkersOnAxis(max_x_marker_value);
}

void Axis::SetYAxisMaxMarkerValue(const float max_marker_value) {
    const std::size_t max_y_marker_value = CalculateAxisMarkerUpperBoundValue(max_marker_value);
    plotting_data_->SetMaxYMarkerValue(max_y_marker_value);
    y_axis_marker_count_ = GenerateNumberOfMarkersOnAxis(max_y_marker_value);
}

/// @todo: max_x_marker_value_ and max_y_marker_value_ are not used anymore! Rewrite this.
std::size_t Axis::ReserveAxisShapeSpace() const {
    constexpr std::size_t number_of_axis{2};
    constexpr std::size_t number_of_zero_markers{2};
    return x_axis_marker_count_ + y_axis_marker_count_ + number_of_axis + number_of_zero_markers;
}

void Axis::CreateAxis() {
    plotting_data_->SetAxisShapes(CreateAxisShapes());
    plotting_data_->SetAxisMarkerValues(CreateAxisMarkerValues());
}

std::vector<sf::RectangleShape> Axis::CreateAxisShapes() {
    std::vector<sf::RectangleShape> axis_shapes;

    axis_shapes.emplace_back(CreateAxisShapeSkeleton(Config::X_AXIS_DIMENSION, 0.0));
    axis_shapes.emplace_back(CreateAxisShapeSkeleton(Config::Y_AXIS_DIMENSION, 180.0));

    const auto x_axis_marker_shapes = CreateXAxisMarkerShapes();
    std::move(x_axis_marker_shapes.cbegin(), x_axis_marker_shapes.cend(), std::back_inserter(axis_shapes));

    const auto y_axis_marker_shapes = CreateYAxisMarkerShapes();
    std::move(y_axis_marker_shapes.cbegin(), y_axis_marker_shapes.cend(), std::back_inserter(axis_shapes));

    return axis_shapes;
}

std::vector<sf::RectangleShape> Axis::CreateXAxisMarkerShapes() {
    std::vector<sf::RectangleShape> axis_markers;

    for (std::size_t i{0}; i <= x_axis_marker_count_; i++) {
        const float position_offset_percentage = static_cast<float>(i) / x_axis_marker_count_;

        sf::RectangleShape axis_marker{CreateAxisShapeSkeleton(Config::MARKER_DIMENSION, 90.0)};
        axis_marker.move({Config::X_AXIS_DIMENSION.x * position_offset_percentage, 0});

        axis_markers.emplace_back(std::move(axis_marker));
    }
    return axis_markers;
}

std::vector<sf::RectangleShape> Axis::CreateYAxisMarkerShapes() {
    std::vector<sf::RectangleShape> axis_markers;

    for (std::size_t i{0}; i <= y_axis_marker_count_; i++) {
        const float position_offset_percentage = static_cast<float>(i) / y_axis_marker_count_;

        sf::RectangleShape axis_marker{CreateAxisShapeSkeleton(Config::MARKER_DIMENSION, 180.0)};
        axis_marker.move({0, -(Config::Y_AXIS_DIMENSION.y * position_offset_percentage)});

        axis_markers.emplace_back(std::move(axis_marker));
    }
    return axis_markers;
}

sf::RectangleShape Axis::CreateAxisShapeSkeleton(const sf::Vector2f &shape_dimension, const float angle = 0) {
    sf::RectangleShape axis_shape;
    axis_shape.setPosition(Config::REFERENCE_POINT);
    axis_shape.setSize(shape_dimension);
    axis_shape.setRotation(angle);
    axis_shape.setFillColor(sf::Color::Black);

    return axis_shape;
}

std::vector<sf::Text> Axis::CreateAxisMarkerValues() {
    constexpr std::size_t number_of_zeros{2};
    const auto max_x_marker_value = plotting_data_->GetMaxXMarkerValue();
    const auto max_y_marker_value = plotting_data_->GetMaxYMarkerValue();

    std::vector<sf::Text> axis_marker_values;
    axis_marker_values.reserve(x_axis_marker_count_ + y_axis_marker_count_ + number_of_zeros);

    const auto x_axis_values = AddValueToAxisMarkers(max_x_marker_value, x_axis_marker_count_, true);
    std::copy(x_axis_values.cbegin(), x_axis_values.cend(), std::back_inserter(axis_marker_values));

    const auto y_axis_values = AddValueToAxisMarkers(max_y_marker_value, y_axis_marker_count_, false);
    std::move(y_axis_values.cbegin(), y_axis_values.cend(), std::back_inserter(axis_marker_values));

    return axis_marker_values;
}

std::vector<sf::Text>
Axis::AddValueToAxisMarkers(std::size_t max_marker_value, std::size_t marker_count, bool is_x_axis) {
    std::vector<sf::Text> axis_marker_values;
    axis_marker_values.reserve(marker_count);

    const std::size_t scaled_marker_value_offset = max_marker_value / marker_count;

    for (std::size_t i{0}; i <= marker_count; i++) {
        const float position_offset_percentage = static_cast<float>(i) / marker_count;
        axis_marker_values.emplace_back(
                CreateMarkerValueText(i * scaled_marker_value_offset, is_x_axis, position_offset_percentage));
    }
    return axis_marker_values;
}

sf::Text Axis::CreateMarkerValueText(const std::size_t value, bool is_x_axis, const float offset_percentage) {
    Config::Global::SetFont();
    sf::Text axis_marker_value_text;
    axis_marker_value_text.setFont(Config::Global::FONT);
    axis_marker_value_text.setFillColor(sf::Color::Black);
    axis_marker_value_text.setCharacterSize(Config::AXIS_FONT_SIZE);
    axis_marker_value_text.setString(std::to_string(value));

    if (is_x_axis) {
        axis_marker_value_text.setPosition(Config::X_AXIS_MARKER_REFERENCE_POINT);
        axis_marker_value_text.move({Config::X_AXIS_DIMENSION.x * offset_percentage, 0});
    } else {
        axis_marker_value_text.setPosition(Config::Y_AXIS_MARKER_REFERENCE_POINT);
        axis_marker_value_text.move({0, -(Config::Y_AXIS_DIMENSION.y * offset_percentage)});
    }

    return axis_marker_value_text;
}

std::size_t Axis::CalculateAxisMarkerUpperBoundValue(float max_value) {
    if (max_value - std::floor(max_value) > 0.5) {
        return std::floor(max_value / 10) * 10 + 10;
    } else {
        return std::floor(max_value / 10) * 10 + 5;
    }
}

std::size_t Axis::GenerateNumberOfMarkersOnAxis(const std::size_t max_marker_value) {
    std::size_t markers_count{Config::Axis::MAX_NUMBER_OF_MARKERS};

    for (std::size_t i{Config::Axis::MAX_NUMBER_OF_MARKERS}; i >= Config::Axis::MIN_NUMBER_OF_MARKERS; i--) {
        if (max_marker_value % i == 0) {
            markers_count = i;
        }
    }
    return markers_count;
}
