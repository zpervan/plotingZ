#include "Plot/Common/src/axis.h"
#include "Plot/Common/src/config.h"

#include <cmath>

void Axis::CreateAxis() {
  AssignAxisMarkersUpperBoundValue();
  AssignAxisMarkerCount();
  plotting_data_->SetAxisShapes(CreateAxisShapes());
  plotting_data_->SetAxisMarkerValues(CreateAxisMarkerValues());
}

void Axis::AssignAxisMarkersUpperBoundValue() {
  const float max_x_value{plotting_data_->GetMaxXValue()};
  const uint64_t max_x_marker_value{CalculateAxisMarkerUpperBoundValue(max_x_value)};
  plotting_data_->SetMaxXMarkerValue(max_x_marker_value);

  const float max_y_value{plotting_data_->GetMaxYValue()};
  const uint64_t max_y_marker_value{CalculateAxisMarkerUpperBoundValue(max_y_value)};
  plotting_data_->SetMaxYMarkerValue(max_y_marker_value);
}

void Axis::AssignAxisMarkerCount() {
  x_axis_marker_count_ = GenerateNumberOfAxisMarkers(plotting_data_->GetMaxXMarkerValue());
  y_axis_marker_count_ = GenerateNumberOfAxisMarkers(plotting_data_->GetMaxYMarkerValue());
}

std::vector<sf::RectangleShape> Axis::CreateAxisShapes() {
  std::vector<sf::RectangleShape> axis_shapes;
  axis_shapes.reserve(ReserveAxisShapeSpace());

  const auto &x_axis{CreateAxisSkeletonShape(Config::X_AXIS_DIMENSION, 0.0)};
  axis_shapes.emplace_back(x_axis);

  const auto &x_axis_marker_shapes{CreateXAxisMarkerShapes()};
  std::move(x_axis_marker_shapes.cbegin(), x_axis_marker_shapes.cend(), std::back_inserter(axis_shapes));

  const auto &y_axis{CreateAxisSkeletonShape(Config::Y_AXIS_DIMENSION, 180.0)};
  axis_shapes.emplace_back(y_axis);

  const auto &y_axis_marker_shapes{CreateYAxisMarkerShapes()};
  std::move(y_axis_marker_shapes.cbegin(), y_axis_marker_shapes.cend(), std::back_inserter(axis_shapes));

  return axis_shapes;
}

std::vector<sf::Text> Axis::CreateAxisMarkerValues() {
  const auto max_x_marker_value{plotting_data_->GetMaxXMarkerValue()};
  const auto &x_axis_values{AddValueToAxisMarkers(max_x_marker_value, x_axis_marker_count_, true)};

  const auto max_y_marker_value{plotting_data_->GetMaxYMarkerValue()};
  const auto &y_axis_values{AddValueToAxisMarkers(max_y_marker_value, y_axis_marker_count_, false)};

  std::vector<sf::Text> axis_marker_values;
  axis_marker_values.reserve(x_axis_marker_count_ + y_axis_marker_count_);

  std::move(x_axis_values.cbegin(), x_axis_values.cend(), std::back_inserter(axis_marker_values));
  std::move(y_axis_values.cbegin(), y_axis_values.cend(), std::back_inserter(axis_marker_values));

  return axis_marker_values;
}

/// @todo: Move to a utility class?
/// @todo: Consider negative values as upper bound
uint64_t Axis::CalculateAxisMarkerUpperBoundValue(float max_value) {
  if (max_value < 10) {
    return std::floor(max_value) + 1;
  }

  if ((max_value - std::floor(max_value)) > 0.5) {
    return std::floor(max_value / 10) * 10 + 10;
  } else {
    return std::floor(max_value / 10) * 10 + 5;
  }
}

uint8_t Axis::GenerateNumberOfAxisMarkers(const std::size_t max_marker_value) {
  std::size_t markers_count{Config::Axis::MAX_NUMBER_OF_MARKERS};

  for (std::size_t i{Config::Axis::MAX_NUMBER_OF_MARKERS}; i >= Config::Axis::MIN_NUMBER_OF_MARKERS; i--) {
    if (max_marker_value % i == 0) {
      markers_count = i;
    }
  }
  constexpr std::size_t zero_marker_count{1};
  return markers_count + zero_marker_count;
}

uint8_t Axis::ReserveAxisShapeSpace() const {
  constexpr std::size_t axis_count{2};
  return axis_count + x_axis_marker_count_ + y_axis_marker_count_;
}

sf::RectangleShape Axis::CreateAxisSkeletonShape(const sf::Vector2f &shape_dimension, const float angle = 0) {
  sf::RectangleShape axis_shape;
  axis_shape.setPosition(Config::REFERENCE_POINT);
  axis_shape.setSize(shape_dimension);
  axis_shape.setRotation(angle);
  axis_shape.setFillColor(sf::Color::Black);

  return axis_shape;
}

std::vector<sf::RectangleShape> Axis::CreateXAxisMarkerShapes() {
  std::vector<sf::RectangleShape> x_axis_markers;
  x_axis_markers.reserve(x_axis_marker_count_);

  // Starting at element index 0, Y axis marker count is subtracted with -1 in order to get the correct axis
  // marker shape position percentage!
  const auto x_axis_marker_count{x_axis_marker_count_ - 1};

  for (std::size_t i{0}; i <= x_axis_marker_count; i++) {
    const float position_percentage_on_x_axis{static_cast<float>(i) / x_axis_marker_count};

    sf::RectangleShape axis_marker{CreateAxisSkeletonShape(Config::MARKER_DIMENSION, 90.0)};
    sf::Vector2f x_offset{
        Config::X_AXIS_DIMENSION.x * position_percentage_on_x_axis + Config::AXIS_LINE_THICKNESS, 0};
    axis_marker.move(x_offset);

    x_axis_markers.emplace_back(std::move(axis_marker));
  }
  return x_axis_markers;
}

std::vector<sf::RectangleShape> Axis::CreateYAxisMarkerShapes() {
  std::vector<sf::RectangleShape> y_axis_markers;
  y_axis_markers.reserve(y_axis_marker_count_);

  // Starting at element index 0, X axis marker count is subtracted with -1 in order to get the correct axis
  // marker shape position percentage!
  const auto y_axis_marker_count{y_axis_marker_count_ - 1};

  for (std::size_t i{0}; i <= y_axis_marker_count; i++) {
    sf::RectangleShape axis_marker{CreateAxisSkeletonShape(Config::MARKER_DIMENSION, 180.0)};

    const float position_percentage_on_y_axis{static_cast<float>(i) / y_axis_marker_count};
    sf::Vector2f y_offset{0, -(Config::Y_AXIS_DIMENSION.y * position_percentage_on_y_axis)};
    axis_marker.move(y_offset);

    y_axis_markers.emplace_back(std::move(axis_marker));
  }
  return y_axis_markers;
}

std::vector<sf::Text> Axis::AddValueToAxisMarkers(std::size_t max_marker_value, std::size_t marker_count,
                                                  bool is_x_axis) {
  std::vector<sf::Text> axis_marker_values;
  axis_marker_values.reserve(marker_count);

  const auto subtracted_marker_count{marker_count - 1};
  const auto scaled_marker_value{max_marker_value / subtracted_marker_count};

  for (std::size_t i{0}; i <= subtracted_marker_count; i++) {

    sf::Text marker_value{CreateMarkerValueSkeleton()};
    marker_value.setString(std::to_string(i * scaled_marker_value));

    const float position_offset_percentage{static_cast<float>(i) / subtracted_marker_count};
    if (is_x_axis) {
      marker_value.setPosition(CalculateMarkerValueXAxisPosition(position_offset_percentage));
    } else {
      marker_value.setPosition(CalculateMarkerValueYAxisPosition(position_offset_percentage));
    }

    axis_marker_values.emplace_back(std::move(marker_value));
  }
  return axis_marker_values;
}

sf::Text Axis::CreateMarkerValueSkeleton() {
  Config::Global::SetFont();

  sf::Text axis_marker_value;
  axis_marker_value.setFont(Config::Global::FONT);
  axis_marker_value.setFillColor(sf::Color::Black);
  axis_marker_value.setCharacterSize(Config::AXIS_FONT_SIZE);

  return axis_marker_value;
}

sf::Vector2f Axis::CalculateMarkerValueXAxisPosition(float offset) const {
  const float marker_value_x_position{Config::X_AXIS_MARKER_REFERENCE_POINT.x +
                                      (Config::X_AXIS_DIMENSION.x * offset)};
  const float marker_value_y_position{Config::X_AXIS_MARKER_REFERENCE_POINT.y};
  return {marker_value_x_position, marker_value_y_position};
}

sf::Vector2f Axis::CalculateMarkerValueYAxisPosition(float offset) const {
  const float marker_value_x_position{Config::Y_AXIS_MARKER_REFERENCE_POINT.x};
  const float marker_value_y_position{Config::Y_AXIS_MARKER_REFERENCE_POINT.y -
                                      (Config::Y_AXIS_DIMENSION.y * offset)};
  return {marker_value_x_position, marker_value_y_position};
}
