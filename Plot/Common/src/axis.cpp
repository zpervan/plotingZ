#include "axis.h"
#include "config.h"


void Axis::SetXAxisSize(const std::size_t size) {
    x_axis_size_ = size;
}

void Axis::SetYAxisSize(const std::size_t size) {
    y_axis_size_ = size;
}

const std::vector<sf::RectangleShape> Axis::DrawAxis() {
    axis_shape_.emplace_back(CreateXAxis());
    axis_shape_.emplace_back(CreateYAxis());
    return axis_shape_;
}

sf::RectangleShape Axis::CreateXAxis() {
    sf::RectangleShape x_axis;
    x_axis.setPosition({Config::ReferencePoint.x, Config::ReferencePoint.y});
    x_axis.setSize({Config::WindowWidth - 40.f, 2.f});
    x_axis.setFillColor(sf::Color::Black);

    return x_axis;
}

sf::RectangleShape Axis::CreateYAxis() {
    sf::RectangleShape y_axis;
    y_axis.setPosition({Config::ReferencePoint.x, Config::ReferencePoint.y});
    y_axis.setSize({2.f, Config::WindowHeight - 40.f});
    y_axis.setRotation(180.f);
    y_axis.setFillColor(sf::Color::Black);

    return y_axis;
}

const std::vector<sf::RectangleShape> Axis::DrawAxisMarkers(std::size_t marker_count, bool is_y_axis) {

    std::vector<sf::RectangleShape> axis_markers;
    for (std::size_t i{0}; i < marker_count; i++) {
        sf::RectangleShape axis_marker;
//        axis_marker.setPosition();
    }
    return std::vector<sf::RectangleShape>();
}

