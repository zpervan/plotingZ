#ifndef PLOTINGZ_LEGEND_H
#define PLOTINGZ_LEGEND_H

#include "Plot/Common/src/plotting_data.h"

class Legend {
public:
  explicit Legend(PlottingData *plotting_data) : plotting_data_(plotting_data){};
  Legend() = default;
  ~Legend() = default;

  /// @brief Set the text/name for the legend labels
  /// @param labels Texts/names for given data
  void SetLegendLabels(const std::vector<std::string> &labels);

  /// @brief Creates the legend with names for each label
  void CreateLegend();

  const std::vector<std::string> &GetLabels() const;

protected:
  std::vector<sf::RectangleShape> CreateLabelColourBoxes();
  std::vector<sf::Text> CreateLabelText();
  sf::RectangleShape CreateLegendFrame();
  void CalculateLegendFrameDimension();
  void CalculateLegendFramePosition();
  float CalculateLabelColourBoxXPosition();
  float CalculateLabelColourBoxYPosition(const size_t position_offset);
  float CalculateLabelTextXPosition();
  float CalculateLabelTextYPosition(std::size_t position_offset);

  std::vector<std::string> labels_{};
  sf::Vector2f legend_frame_dimension_{0.0, 0.0};
  sf::Vector2f legend_frame_position_{0.0, 0.0};
  PlottingData *plotting_data_{nullptr};
  bool IsLegendFrameDimensionCalculated() const;
};

#endif // PLOTINGZ_LEGEND_H
