#include "axis.h"
#include "ThirdParty/fmt/include/fmt/format.h"
#include "config.h"

void Axis::SetXAxis(const std::size_t size) { x_axis_size_ = size; }

void Axis::SetYAxis(const std::size_t size) { y_axis_size_ = size; }

std::size_t Axis::ReserveAxisShapeSpace() const {
    constexpr std::size_t number_of_axis{2};
    constexpr std::size_t number_of_zero_markers{2};
    return x_axis_size_ + y_axis_size_ + number_of_axis + number_of_zero_markers;
}

void Axis::CreateAxis() {
    axis_shapes_.reserve(ReserveAxisShapeSpace());

    axis_shapes_.emplace_back(CreateXAxis());
    axis_shapes_.emplace_back(CreateYAxis());

    const auto x_axis_markers = CreateAxisMarkers(x_axis_size_, true);
    std::move(x_axis_markers.cbegin(), x_axis_markers.cend(), std::back_inserter(axis_shapes_));

    const auto y_axis_markers = CreateAxisMarkers(y_axis_size_, false);
    std::move(y_axis_markers.cbegin(), y_axis_markers.cend(), std::back_inserter(axis_shapes_));

    constexpr std::size_t number_of_zeros{2};
    axis_marker_values_.reserve(x_axis_size_ + y_axis_size_ + number_of_zeros);

    const auto x_axis_values = AddAxisMarkerValues(x_axis_size_, true);
    std::copy(x_axis_values.cbegin(), x_axis_values.cend(), std::back_inserter(axis_marker_values_));

    const auto y_axis_values = AddAxisMarkerValues(y_axis_size_, false);
    std::move(y_axis_values.cbegin(), y_axis_values.cend(), std::back_inserter(axis_marker_values_));
}

std::vector<sf::RectangleShape> Axis::GetAxisShapes() const {
    return axis_shapes_;
}

std::vector<sf::Text> Axis::GetAxisMarkerValues() const {
    return axis_marker_values_;
}

sf::RectangleShape Axis::CreateXAxis() {
    sf::RectangleShape x_axis;
    x_axis.setPosition(Config::REFERENCE_POINT);
    x_axis.setSize(Config::X_AXIS_DIMENSION);
    x_axis.setFillColor(sf::Color::Black);

    return x_axis;
}

sf::RectangleShape Axis::CreateYAxis() {
    sf::RectangleShape y_axis;
    y_axis.setPosition(Config::REFERENCE_POINT);
    y_axis.setSize(Config::Y_AXIS_DIMENSION);
    y_axis.setRotation(180.f);
    y_axis.setFillColor(sf::Color::Black);

    return y_axis;
}

std::vector<sf::RectangleShape>
Axis::CreateAxisMarkers(const std::size_t axis_size, bool is_x_axis) {

    std::vector<sf::RectangleShape> axis_markers;
    axis_markers.reserve(axis_size);

    for (std::size_t i{0}; i <= axis_size; i++) {
        sf::RectangleShape axis_marker;
        axis_marker.setPosition(Config::REFERENCE_POINT);
        axis_marker.setSize(Config::MARKER_DIMENSION);
        axis_marker.setFillColor(sf::Color::Black);

        const float offset_percentage = static_cast<float>(i) / axis_size;

        if (is_x_axis) {
            axis_marker.rotate(90.f);
            axis_marker.move({Config::X_AXIS_DIMENSION.x * offset_percentage, 0});
        } else {
            axis_marker.setRotation(180.f);
            axis_marker.move({0, -(Config::Y_AXIS_DIMENSION.y * offset_percentage)});
        }

        axis_markers.emplace_back(std::move(axis_marker));
    }
    return axis_markers;
}

std::vector<sf::Text>
Axis::AddAxisMarkerValues(const std::size_t marker_count, bool is_x_axis) {
    std::vector<sf::Text> axis_marker_values;
    axis_marker_values.reserve(marker_count);

    for (std::size_t i{0}; i <= marker_count; i++) {
        const float offset_percentage = static_cast<float>(i) / marker_count;
        axis_marker_values.emplace_back(CreateMarkerValueText(i, is_x_axis, offset_percentage));
    }
    return axis_marker_values;
}

sf::Text Axis::CreateMarkerValueText(const std::size_t value, bool is_x_axis, const float offset_percentage) {
    Global::SetFont();
    sf::Text axis_marker_value_text;
    axis_marker_value_text.setFont(Config::FONT);
    axis_marker_value_text.setFillColor(sf::Color::Black);
    axis_marker_value_text.setCharacterSize(Config::FONT_SIZE);
    axis_marker_value_text.setString(std::to_string(value));

    if (is_x_axis) {
        axis_marker_value_text.setPosition(Config::X_AXIS_REFERENCE_POINT);
        axis_marker_value_text.move({Config::X_AXIS_DIMENSION.x * offset_percentage, 0});
    } else {
        axis_marker_value_text.setPosition(Config::Y_AXIS_REFERENCE_POINT);
        axis_marker_value_text.move({0, -(Config::Y_AXIS_DIMENSION.y * offset_percentage)});
    }

    return axis_marker_value_text;
}
