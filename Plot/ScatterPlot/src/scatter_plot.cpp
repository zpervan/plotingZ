#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "Plot/Common/src/config.h"

#include <algorithm>

void ScatterPlot::Plot() {

    /// @todo: Check if size of xy data containers are equal
    if (x_data_.empty() || y_data_.empty()) {
        throw std::invalid_argument("Input (XY) data is not set");
    }

    CreateAxis();
    CreateDataPoints();

    sf::RenderWindow window{{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}, title_};
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);

        for (const auto &shape : GetAxisShapes()) {
            window.draw(shape);
        }

        for (const auto &marker_value : GetAxisMarkerValues()) {
            window.draw(marker_value);
        }

        for (const auto &data_point : GetDataPoints()) {
            window.draw(data_point);
        }

        window.display();
    }
}

const std::vector<float> &ScatterPlot::GetXData() const {
    return x_data_;
}

const std::vector<float> &ScatterPlot::GetYData() const {
    return y_data_;
}

void ScatterPlot::SetData(const std::vector<float> &x_data, const std::vector<float> &y_data) {
    x_max_element_ = MaxElement(x_data);
    y_max_element_ = MaxElement(y_data);

    SetXAxis(x_max_element_);
    SetYAxis(y_max_element_);

    x_data_.reserve(x_data.size());
    std::move(x_data.cbegin(), x_data.cend(), std::back_inserter(x_data_));

    y_data_.reserve(y_data.size());
    std::move(y_data.cbegin(), y_data.cend(), std::back_inserter(y_data_));
}

void ScatterPlot::SetTitle(const std::string &title) {
    title_ = title;
}

void ScatterPlot::CreateDataPoints() {
    data_points_.reserve(x_data_.size());

    for (std::size_t i{0}; i < x_data_.size(); i++) {
        sf::CircleShape data_point;
        data_point.setRadius(3.f);
        data_point.setPosition(Config::REFERENCE_POINT);
        data_point.setFillColor(sf::Color::Red);

        const float normalized_x_data_point = x_data_.at(i) / x_max_element_;
        const float normalized_y_data_point = y_data_.at(i) / y_max_element_;
        data_point.move(
                {Config::X_AXIS_DIMENSION.x * normalized_x_data_point,
                 -Config::Y_AXIS_DIMENSION.y * normalized_y_data_point});

        data_points_.emplace_back(data_point);
    }
}

/// @todo: Consider moving it to a common utility class
const float ScatterPlot::MaxElement(const std::vector<float> &elements) {
    return *std::max_element(elements.cbegin(), elements.cend());
}

const std::vector<sf::CircleShape> &ScatterPlot::GetDataPoints() const {
    return data_points_;
}
