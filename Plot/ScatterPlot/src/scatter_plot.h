#ifndef PLOTINGZ_SCATTER_PLOT_H
#define PLOTINGZ_SCATTER_PLOT_H

#include "Plot/Common/src/plotting_data.h"

#include <SFML/System/Vector2.hpp>

/// @brief Contains the logic for converting input data to points/dots/circle shapes.
class ScatterPlot {
 public:
  explicit ScatterPlot(PlottingData *plotting_data) : plotting_data_(plotting_data) {};
  ScatterPlot() = default;
  ~ScatterPlot() = default;
  ScatterPlot(ScatterPlot &&source) noexcept = delete;
  ScatterPlot &operator=(ScatterPlot &&rhs) noexcept;
  ScatterPlot(const ScatterPlot &source) = delete;
  ScatterPlot &operator=(const ScatterPlot &rhs) = delete;

  /// @brief Creates data points from given raw input data.
  void CreateScatterPlot();

 protected:

  sf::CircleShape CreateCircleDataPointSkeleton() const;
  sf::Vector2f CalculateDataPointPosition(const sf::Vector2f &normalized_point) const;

  PlottingData
	  *plotting_data_{nullptr};
  std::size_t color_count_{0};
};

#endif //PLOTINGZ_SCATTER_PLOT_H
