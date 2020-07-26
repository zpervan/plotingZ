#include "axis.h"
#include "config.h"


void Axis::SetXAxisSize(const std::size_t size) {
    x_axis_size_ = size;
}

void Axis::SetYAxisSize(const std::size_t size) {
    y_axis_size_ = size;
}

void Axis::DrawAxis() {
//    std::for_each(axis_shape_.cbegin(), axis_shape_.cend(),[]());
}

//sf::RectangleShape Axis::DrawXAxis() {
//    sf::RectangleShape x_axis;
//    x_axis.setPosition({20, Config::WindowHeight - 20});
//    x_axis.setSize({Config::WindowWidth - 40.f, 1.f});
//    x_axis.setFillColor(sf::Color::Black);
//
//    return x_axis;
//}
//
//
//sf::RectangleShape Axis::DrawYAxis() {
//    sf::RectangleShape y_axis;
//    y_axis.setPosition({20, Config::WindowHeight - 20});
//    y_axis.setSize({1.f, Config::WindowHeight - 40.f});
//    y_axis.setRotation(180.f);
//    y_axis.setFillColor(sf::Color::Black);
//
//    return y_axis;
//}
