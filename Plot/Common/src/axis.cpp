#include "axis.h"
#include "config.h"


void Axis::SetXAxis(const std::size_t size) {
    x_axis_size_ = size;
}

void Axis::SetYAxis(const std::size_t size) {
    y_axis_size_ = size;
}

const std::vector<sf::RectangleShape> Axis::DrawAxis() {
    axis_shape_.emplace_back(CreateXAxis());
    axis_shape_.emplace_back(CreateYAxis());

    const auto x_axis_markers = CreateAxisMarkers(x_axis_size_, true);
    std::move(x_axis_markers.cbegin(), x_axis_markers.cend(), std::back_inserter(axis_shape_));

    const auto y_axis_markers = CreateAxisMarkers(y_axis_size_, false);
    std::move(y_axis_markers.cbegin(), y_axis_markers.cend(), std::back_inserter(axis_shape_));

    return axis_shape_;
}

std::vector<sf::RectangleShape> Axis::GetAxisShapes() {
    return axis_shape_;
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

const std::vector<sf::RectangleShape> Axis::CreateAxisMarkers(std::size_t axis_size, bool is_x_axis) {

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
