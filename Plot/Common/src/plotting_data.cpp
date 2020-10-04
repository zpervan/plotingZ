#include "Plot/Common/src/plotting_data.h"
#include "Plot/Common/src/config.h"

void PlottingData::AppendToInputDataValuesCollection(
	const std::vector<float> &input_data_x,
	const std::vector<float> &input_data_y) {
  std::vector<sf::Vector2f> data;
  data.reserve(input_data_x.size());

  for (std::size_t i{0}; i < input_data_x.size(); i++) {
	data.emplace_back(sf::Vector2f{input_data_x.at(i), input_data_y.at(i)});
  }
  input_data_values_collection_->emplace_back(data);
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
  point_data_collection_->emplace_back(std::move(data_points));
}

void PlottingData::EmplaceDataLinesCollections(DataLines &data_lines) {
  line_data_collection_->emplace_back(std::move(data_lines));
}

/// Setters
void PlottingData::SetAxisShapes(
	std::vector<sf::RectangleShape> &&axis_shapes) {
  *axis_shapes_ = std::move(axis_shapes);
}

void PlottingData::SetAxisMarkerValues(
	std::vector<sf::Text> &&axis_marker_values) {
  std::move(axis_marker_values.begin(), axis_marker_values.end(),
			std::back_inserter(*axis_marker_values_));
}

void PlottingData::SetLegendShapes(
	std::vector<sf::RectangleShape> &legend_shapes) {
  *legend_shapes_ = std::move(legend_shapes);
}

void PlottingData::SetLegendLabels(std::vector<sf::Text> &legend_labels) {
  *legend_labels_ = std::move(legend_labels);
}

void PlottingData::SetTitle(const std::string &title) { title_ = title; }

void PlottingData::SetMaxXMarkerValue(size_t maxXMarkerValue) {
  max_x_marker_value_ = maxXMarkerValue;
}

void PlottingData::SetMaxYMarkerValue(size_t maxYMarkerValue) {
  max_y_marker_value_ = maxYMarkerValue;
}

void PlottingData::SetMinXMarkerValue(size_t minXMarkerValue) {
  min_x_marker_value_ = minXMarkerValue;
}

void PlottingData::SetMinYMarkerValue(size_t minYMarkerValue) {
  min_y_marker_value_ = minYMarkerValue;
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

const std::vector<sf::Text> &PlottingData::GetLegendLabelTexts() const {
  return *legend_labels_;
}

float PlottingData::GetMaxXValue() const { return max_x_value_; }

float PlottingData::GetMaxYValue() const { return max_y_value_; }

const std::vector<DataPoints> &PlottingData::GetPointDataCollection() const {
  return *point_data_collection_;
}

const std::vector<DataLines> &PlottingData::GetLineDataValueCollection() const {
  return *line_data_collection_;
}

const std::vector<InputDataValues> &PlottingData::GetInputDataValuesCollection() const {
  return *input_data_values_collection_;
}

size_t PlottingData::GetMaxXMarkerValue() const { return max_x_marker_value_; }

size_t PlottingData::GetMaxYMarkerValue() const { return max_y_marker_value_; }

size_t PlottingData::GetMinXMarkerValue() const { return min_x_marker_value_; }

size_t PlottingData::GetMinYMarkerValue() const { return min_y_marker_value_; }
