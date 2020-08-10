#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "Plot/Common/src/config.h"
#include "Plot/Common/src/types.h"

#include <algorithm>

void ScatterPlot::Plot() {

    if (xy_data_.empty()) {
        throw std::invalid_argument("Data is not set!");
    }

    SetAxis();
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

        for (const auto &data_points : GetDataPointsCollections()) {
            for (const auto &data_point : data_points) {
                window.draw(data_point);
            }
        }

        window.display();
    }
}

void ScatterPlot::SetData(const std::vector<float> &x_data, const std::vector<float> &y_data) {
    if (x_data.empty() || y_data.empty()) {
        throw std::invalid_argument("Input data is empty! Check data,");
    }


    if (x_data.size() != y_data.size()) {
        throw std::invalid_argument("Size of given input XY data does not match! Check data.");
    }

    std::vector<float> x_data_points;
    x_data_points.reserve(x_data.size());
    std::move(x_data.cbegin(), x_data.cend(), std::back_inserter(x_data_points));

    std::vector<float> y_data_points;
    y_data_points.reserve(y_data.size());
    std::move(y_data.cbegin(), y_data.cend(), std::back_inserter(y_data_points));

    SetMaxXElement(x_data);
    SetMaxYElement(y_data);

    xy_data_.emplace_back(XYData{x_data_points, y_data_points});
}

void ScatterPlot::SetTitle(const std::string &title) {
    title_ = title;
}

void ScatterPlot::SetAxis() {
    SetXAxis(x_max_element_);
    SetYAxis(y_max_element_);
}

sf::CircleShape ScatterPlot::CreateCircleDataPointSkeleton() {
    sf::CircleShape data_point_skeleton;
    data_point_skeleton.setRadius(3.f);
    data_point_skeleton.setPosition(Config::REFERENCE_POINT);
    data_point_skeleton.setFillColor(mapped_colors.at(color_count_));

    return data_point_skeleton;
}

void ScatterPlot::CreateDataPoints() {

    std::vector<sf::CircleShape> data_points;
    for (std::size_t i{0}; i < xy_data_.size(); i++) {
        const auto &x_data = xy_data_.at(i).first;
        const auto &y_data = xy_data_.at(i).second;

        for (std::size_t j{0}; j < x_data.size(); j++) {

            sf::CircleShape data_point = CreateCircleDataPointSkeleton();
            const float normalized_x_data_point = x_data.at(j) / x_max_element_;
            const float normalized_y_data_point = y_data.at(j) / y_max_element_;

            data_point.move(
                    {Config::X_AXIS_DIMENSION.x * normalized_x_data_point,
                     -Config::Y_AXIS_DIMENSION.y * normalized_y_data_point});
            data_points.emplace_back(data_point);
        }
        ++color_count_;
        data_points_collections_.emplace_back(data_points);
    }
}

/// @todo: Consider moving it to a common utility class
void ScatterPlot::SetMaxXElement(const std::vector<float> &x_data) {
    const float max_x_value = *std::max_element(x_data.cbegin(), x_data.cend());
    if (max_x_value > x_max_element_) {
        x_max_element_ = max_x_value;
    }
}

void ScatterPlot::SetMaxYElement(const std::vector<float> &y_data) {
    const float max_y_value = *std::max_element(y_data.cbegin(), y_data.cend());
    if (max_y_value > y_max_element_) {
        y_max_element_ = max_y_value;
    }
}

const std::vector<std::vector<sf::CircleShape>> &ScatterPlot::GetDataPointsCollections() const {
    return data_points_collections_;
}


