#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "Plot/Common/src/config.h"
#include "Plot/Common/src/types.h"
#include <assert.h>
#include <algorithm>

ScatterPlot::ScatterPlot(ScatterPlot &&source) noexcept {
    this->plotting_data_ = source.plotting_data_;
    this->color_count_ = source.color_count_;
}

ScatterPlot &ScatterPlot::operator=(ScatterPlot &&rhs) noexcept {
    if (this != &rhs) {
        this->plotting_data_ = rhs.plotting_data_;
        this->color_count_ = rhs.color_count_;
    }
    return *this;
}

void ScatterPlot::CreateDataPoints() {

    assert(plotting_data_ != nullptr);

    const auto &input_data_points = plotting_data_->GetInputDataValuesCollection();

    std::vector<sf::CircleShape> points;

    for (const auto &data_points : input_data_points) {
        for (const auto &point : data_points) {
            sf::CircleShape data_point = CreateCircleDataPointSkeleton();
            const float normalized_x_data_point = point.x / plotting_data_->GetMaxXMarkerValue();
            const float normalized_y_data_point = point.y / plotting_data_->GetMaxYMarkerValue();

            data_point.move(
                    {Config::X_AXIS_DIMENSION.x * normalized_x_data_point,
                     -Config::Y_AXIS_DIMENSION.y * normalized_y_data_point});
            points.emplace_back(data_point);
        }
        ++color_count_;
        plotting_data_->EmplaceDataPointsCollections(points);
    }
}

sf::CircleShape ScatterPlot::CreateCircleDataPointSkeleton() const {
    sf::CircleShape data_point_skeleton;
    data_point_skeleton.setRadius(Config::ScatterPlot::DATA_POINT_RADIUS);
    data_point_skeleton.setPosition(Config::REFERENCE_POINT.x - Config::ScatterPlot::DATA_POINT_X_OFFSET,
                                    Config::REFERENCE_POINT.y - Config::ScatterPlot::DATA_POINT_Y_OFFSET);
    data_point_skeleton.setFillColor(mapped_colors.at(color_count_));

    return data_point_skeleton;
}

PlottingData *ScatterPlot::GetPlottingData() const {
    return plotting_data_;
}
