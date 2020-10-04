#ifndef PLOTINGZ_AXIS_H
#define PLOTINGZ_AXIS_H

#include "Plot/Common/src/plotting_data.h"

#include <SFML/Graphics.hpp>

/// @todo: Scale axis values text when values are more than one character
/// @todo: Grid?
/// @todo: Consider smoothing axis lines and a grayish color

class Axis {
 public:
  explicit Axis(PlottingData *plotting_data) : plotting_data_{plotting_data} {}
  Axis() = default;
  ~Axis() = default;
  Axis(const Axis &rhs) = delete;
  Axis &operator=(const Axis &rhs) = delete;
  Axis(Axis &&rhs) = delete;
  Axis &operator=(Axis &&rhs) = delete;

  /// @brief Creates the axis based on given input data
  void CreateAxis();

 private:
  std::vector<sf::RectangleShape> CreateAxisShapes();
  std::vector<sf::RectangleShape> CreateXAxisMarkerShapes();
  std::vector<sf::RectangleShape> CreateYAxisMarkerShapes();
  std::vector<sf::Text> CreateAxisMarkerValues();
  std::vector<sf::Text> AddValueToAxisMarkers(std::size_t max_marker_value, std::size_t marker_count, bool is_x_axis);
  sf::RectangleShape CreateAxisSkeletonShape(const sf::Vector2f &shape_dimension, float angle);
  sf::Text CreateMarkerValueSkeleton();
  sf::Vector2f CalculateMarkerValueXAxisPosition(float offset) const;
  sf::Vector2f CalculateMarkerValueYAxisPosition(float offset) const;
  uint64_t CalculateAxisMarkerUpperBoundValue(float max_value);
  uint8_t ReserveAxisShapeSpace() const;
  uint8_t GenerateNumberOfAxisMarkers(std::size_t max_marker_value);
  void AssignAxisMarkersUpperBoundValue();
  void AssignAxisMarkerCount();

  PlottingData *plotting_data_{nullptr};
  uint8_t x_axis_marker_count_{0};
  uint8_t y_axis_marker_count_{0};
};

#endif //PLOTINGZ_AXIS_H
