#ifndef PLOTINGZ_LINE_PLOT_H
#define PLOTINGZ_LINE_PLOT_H

#include "Plot/Common/src/plotting_data.h"

/// @brief Contains logic for line plot drawing
class LinePlot {
 public:
  explicit LinePlot(PlottingData *plotting_data)
	  : plotting_data_(plotting_data) {}

  LinePlot() = default;
  ~LinePlot() = default;
  LinePlot(const LinePlot &rhs) = delete;
  LinePlot &operator=(const LinePlot &rhs) = delete;
  LinePlot(LinePlot &&rhs) noexcept = delete;
  LinePlot &operator=(LinePlot &&rhs) noexcept = default;

  /// @brief Creates line plot data out of given input 2D data points
  void CreateLinePlot();

 private:
  sf::Vector2f CalculateDataPointPositionOffset(const sf::Vector2f &normalized_point) const;

  PlottingData *plotting_data_{nullptr};
  std::size_t color_count_{0};
};

#endif //PLOTINGZ_LINE_PLOT_H
