#include "Plot/Plots/src/line_plot.h"
#include "Plot/Common/src/config.h"
#include "Plot/Common/src/types.h"
#include "Plot/Utility/src/convert_utility.h"
#include "Plot/Utility/src/math_utility.h"

#include <cassert>
#include <vector>

void LinePlot::CreateLinePlot() {
  assert(plotting_data_ != nullptr);

  const auto &input_data = plotting_data_->GetInputDataValuesCollection();

  std::vector<sf::RectangleShape> lines;

  for (const auto &data : input_data) {
    for (std::size_t i{0}; i < data.size() - 1; i++) {
      const auto &max_x_marker_value = plotting_data_->GetMaxXMarkerValue();
      const auto &max_y_marker_value = plotting_data_->GetMaxYMarkerValue();

      const auto &normalized_origin_point =
          ConvertUtility::NormalizeValues(data.at(i), max_x_marker_value, max_y_marker_value);
      const auto &origin_point_screen_position =
          ConvertUtility::ConvertNormalizedPointToAxisScreenSpace(normalized_origin_point);

      const auto &normalized_end_point =
          ConvertUtility::NormalizeValues(data.at(i + 1), max_x_marker_value, max_y_marker_value);
      const auto &end_point_screen_position =
          ConvertUtility::ConvertNormalizedPointToAxisScreenSpace(normalized_end_point);

      const auto &line_length = MathUtility::CalculateDistanceBetweenTwo2DPoints(origin_point_screen_position,
                                                                                 end_point_screen_position);

      const float angle = MathUtility::CalculateAngleBetweenTwo2DPoints(origin_point_screen_position,
                                                                        end_point_screen_position);

      sf::RectangleShape line;
      line.setFillColor(mapped_colors.at(color_count_));
      line.setSize({line_length, 1});
      // The rotation is performed around the top-left corner of the screen in CCW direction
      line.rotate(-angle);
      line.setPosition(CalculateDataPointPositionOffset(normalized_origin_point));

      lines.emplace_back(std::move(line));
    }
    ++color_count_;
    plotting_data_->EmplaceDataLinesCollections(lines);
  }
}

sf::Vector2f LinePlot::CalculateDataPointPositionOffset(const sf::Vector2f &normalized_point) const {
  const float offsetted_x_value =
      Config::REFERENCE_POINT.x + (Config::X_AXIS_DIMENSION.x * normalized_point.x);
  const float offsetted_y_value =
      Config::REFERENCE_POINT.y - (Config::Y_AXIS_DIMENSION.y * normalized_point.y);

  return {offsetted_x_value, offsetted_y_value};
}
