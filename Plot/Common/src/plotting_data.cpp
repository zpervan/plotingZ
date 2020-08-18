#include "Plot/Common/src/plotting_data.h"
#include "Plot/Common/src/config.h"

void PlottingData::AppendToInputDataValuesCollection(const std::vector<float> &input_data_x,
                                                     const std::vector<float> &input_data_y) {
    input_data_values_collection_->push_back({input_data_x, input_data_y});
}

void PlottingData::FindAndSetMaxXValue(const std::vector<float> &input_data_x) {
    const float max_x_value = *std::max_element(input_data_x.cbegin(), input_data_x.cend());
    if (max_x_value > max_x_value_) {
        max_x_value_ = max_x_value;
    }
}

void PlottingData::FindAndSetMaxYValue(const std::vector<float> &input_data_y) {
    const float max_y_value = *std::max_element(input_data_y.cbegin(), input_data_y.cend());
    if (max_y_value > max_y_value_) {
        max_y_value_ = max_y_value;
    }
}

void PlottingData::EmplaceDataPointsCollections(DataPoints &data_points) {
    data_points_collection_->emplace_back(data_points);
}

/// Setters
void PlottingData::SetAxisShapes(std::vector<sf::RectangleShape> &axis_shapes) {
    *axis_shapes_ = std::move(axis_shapes);
}

void PlottingData::SetAxisMarkerValues(std::vector<sf::Text> &axis_marker_values) {
    std::move(axis_marker_values.begin(), axis_marker_values.end(), std::back_inserter(*axis_marker_values_));
}

void PlottingData::SetLegendShapes(std::vector<sf::RectangleShape> &legend_shapes) {
    *legend_shapes_ = std::move(legend_shapes);
}

void PlottingData::SetLegendLabels(std::vector<sf::Text> &legend_labels) {
    *legend_labels_ = std::move(legend_labels);
}

void PlottingData::SetTitle(const std::string &title) {
    title_ = title;
}

/// Getters
const std::vector<sf::RectangleShape> &PlottingData::GetAxisShapes() const {
    return *axis_shapes_;
}

const std::vector<sf::Text> &PlottingData::GetAxisMarkerValues() const {
    return *axis_marker_values_;
}

const std::vector<sf::RectangleShape> &PlottingData::GetLegendShapes() const {
    return *legend_shapes_;
}

const std::vector<sf::Text> &PlottingData::GetLegendLabels() const {
    return *legend_labels_;
}

float PlottingData::GetMaxXValue() const {
    return max_x_value_;
}

float PlottingData::GetMaxYValue() const {
    return max_y_value_;
}

const std::vector<DataPoints> &PlottingData::GetDataPointsCollections() const {
    return *data_points_collection_;
}

const std::vector<InputDataValues> &PlottingData::GetInputDataValuesCollection() const {
    return *input_data_values_collection_;
}
