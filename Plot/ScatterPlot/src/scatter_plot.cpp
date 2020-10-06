#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "Plot/Common/src/config.h"
#include "Plot/Common/src/types.h"
#include "Plot/Utility/src/convert_utility.h"
#include <cassert>

ScatterPlot &ScatterPlot::operator=(ScatterPlot &&rhs) noexcept {
  if (this != &rhs) {
	plotting_data_ = rhs.plotting_data_;
	color_count_ = rhs.color_count_;
  }
  return *this;
}

void ScatterPlot::CreateScatterPlot() {
  assert(plotting_data_ != nullptr && "Plotting data is not assigned or does not exist!");

  const auto &input_data_values_collection{plotting_data_->GetInputDataValuesCollection()};

  for (const auto &input_data_values : input_data_values_collection) {
	std::vector<sf::CircleShape> points;
	points.reserve(input_data_values.size());

	for (const auto &input_data_value : input_data_values) {
	  sf::CircleShape data_point{CreateCircleDataPointSkeleton()};

	  const auto max_x_marker_value{plotting_data_->GetMaxXMarkerValue()};
	  const auto max_y_marker_value{plotting_data_->GetMaxYMarkerValue()};
	  const auto normalized_data_value
		  {ConvertUtility::NormalizeValues(input_data_value, max_x_marker_value, max_y_marker_value)};
	  data_point.setPosition(CalculateDataPointPosition(normalized_data_value));

	  points.emplace_back(std::move(data_point));
	}
	++color_count_;
	plotting_data_->EmplaceDataPointsCollections(points);
  }
}

sf::CircleShape ScatterPlot::CreateCircleDataPointSkeleton() const {
  sf::CircleShape data_point_skeleton;
  data_point_skeleton.setRadius(Config::ScatterPlot::DATA_POINT_RADIUS);
  data_point_skeleton.setFillColor(mapped_colors.at(color_count_));

  return data_point_skeleton;
}

sf::Vector2f ScatterPlot::CalculateDataPointPosition(const sf::Vector2f &normalized_point) const {
  const float offsetted_reference_point_x{Config::REFERENCE_POINT.x - Config::ScatterPlot::DATA_POINT_X_OFFSET};
  const float data_point_position_x{offsetted_reference_point_x + Config::X_AXIS_DIMENSION.x * normalized_point.x};

  const float offsetted_reference_point_y{Config::REFERENCE_POINT.y - Config::ScatterPlot::DATA_POINT_Y_OFFSET};
  const float data_point_position_y{offsetted_reference_point_y - Config::Y_AXIS_DIMENSION.y * normalized_point.y};

  return {data_point_position_x, data_point_position_y};
}
