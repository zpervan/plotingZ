#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "Plot/Common/src/config.h"
#include "Plot/Common/src/types.h"
#include <assert.h>
#include <algorithm>
#include <iostream>

void ScatterPlot::CreateDataPoints() {

    assert(plotting_data_ != nullptr);

    const auto& input_data_points = plotting_data_->GetInputDataValuesCollection();

    std::vector<sf::CircleShape> data_points;
    for (std::size_t i{0}; i < input_data_points.size(); i++) {
        const auto &x_data = input_data_points.at(i).first;
        const auto &y_data = input_data_points.at(i).second;

        for (std::size_t j{0}; j < x_data.size(); j++) {

            sf::CircleShape data_point = CreateCircleDataPointSkeleton();
            const float normalized_x_data_point = x_data.at(j) / plotting_data_->GetMaxXValue();
            const float normalized_y_data_point = y_data.at(j) / plotting_data_->GetMaxYValue();

            data_point.move(
                    {Config::X_AXIS_DIMENSION.x * normalized_x_data_point,
                     -Config::Y_AXIS_DIMENSION.y * normalized_y_data_point});
            data_points.emplace_back(data_point);
        }
        ++color_count_;
        plotting_data_->SetDataPointsCollections(data_points);
    }
}

sf::CircleShape ScatterPlot::CreateCircleDataPointSkeleton() {
    sf::CircleShape data_point_skeleton;
    data_point_skeleton.setRadius(3.f);
    data_point_skeleton.setPosition(Config::REFERENCE_POINT);
    data_point_skeleton.setFillColor(mapped_colors.at(color_count_));

    return data_point_skeleton;
}

PlottingData *ScatterPlot::GetPlottingData() const {
    return plotting_data_;
}


