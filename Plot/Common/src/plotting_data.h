#ifndef PLOTINGZ_PLOTTING_DATA_H
#define PLOTINGZ_PLOTTING_DATA_H

#include "ThirdParty/SFML/include/SFML/Graphics.hpp"
#include <memory>
#include <vector>

/// @todo: Should we really append the raw input data?
using InputDataValues = std::vector<sf::Vector2f>;
using DataPoints = std::vector<sf::CircleShape>;
using DataLines = std::vector<sf::RectangleShape>;

/// @brief Serves as a central data container for raw and processed data. This
/// data will be used for visualization.
class PlottingData
{
public:
  /// @brief Pairs and appends the raw input data to a vector.
  /// @param [in] input_data_x Raw input data X
  /// @param [in] input_data_y Raw input data Y
  void AppendToInputDataValuesCollection(const std::vector<float> &input_data_x,
                                         const std::vector<float> &input_data_y);

  /// @brief Finds and sets the maximum value (if possible) for given raw input
  /// data X.
  /// @param [in] input_data_x Raw input data X
  void FindAndSetMaxXValue(const std::vector<float> &input_data_x);

  /// @brief Finds and sets the maximum value (if possible) for given raw input
  /// data Y.
  /// @param [in] input_data_y Raw input data Y
  void FindAndSetMaxYValue(const std::vector<float> &input_data_y);

  /// @brief Adds data points to a vector of data points collection
  /// @param [in] data_points Processed circle shaped data
  void EmplaceDataPointsCollections(DataPoints &data_points);

  /// @brief Adds data lines to a vector of data lines collection
  /// @param [in] data_lines Processed rectangle/line shaped data
  void EmplaceDataLinesCollections(DataLines &data_lines);

  /// @section Setters

  void SetAxisShapes(std::vector<sf::RectangleShape> &&axis_shapes);
  void SetAxisMarkerValues(std::vector<sf::Text> &&axis_marker_values);
  void SetLegendShapes(std::vector<sf::RectangleShape> &legend_shapes);
  void SetLegendLabels(std::vector<sf::Text> &legend_labels);
  void SetTitle(const std::string &title);
  void SetMaxXMarkerValue(size_t maxXMarkerValue);
  void SetMaxYMarkerValue(size_t maxYMarkerValue);
  void SetMinXMarkerValue(size_t minXMarkerValue);
  void SetMinYMarkerValue(size_t minYMarkerValue);

  /// @section Getters

  const std::vector<sf::RectangleShape> &GetAxisShapes() const;
  const std::vector<sf::Text> &GetAxisMarkerValues() const;
  const std::vector<sf::RectangleShape> &GetLegendShapes() const;
  const std::vector<sf::Text> &GetLegendLabelTexts() const;
  float GetMaxXValue() const;
  float GetMaxYValue() const;
  const std::vector<DataPoints> &GetPointDataCollection() const;
  const std::vector<DataLines> &GetLineDataValueCollection() const;
  const std::vector<InputDataValues> &GetInputDataValuesCollection() const;
  std::size_t GetMaxXMarkerValue() const;
  std::size_t GetMaxYMarkerValue() const;
  std::size_t GetMinXMarkerValue() const;
  std::size_t GetMinYMarkerValue() const;

protected:
  std::unique_ptr<std::vector<InputDataValues>> input_data_values_collection_ =
      std::make_unique<std::vector<InputDataValues>>();
  std::unique_ptr<std::vector<DataPoints>> point_data_collection_ =
      std::make_unique<std::vector<DataPoints>>();
  std::unique_ptr<std::vector<DataLines>> line_data_collection_ = std::make_unique<std::vector<DataLines>>();
  std::unique_ptr<std::vector<sf::RectangleShape>> axis_shapes_ =
      std::make_unique<std::vector<sf::RectangleShape>>();
  std::unique_ptr<std::vector<sf::Text>> axis_marker_values_ = std::make_unique<std::vector<sf::Text>>();
  std::unique_ptr<std::vector<sf::RectangleShape>> legend_shapes_ =
      std::make_unique<std::vector<sf::RectangleShape>>();
  std::unique_ptr<std::vector<sf::Text>> legend_labels_ = std::make_unique<std::vector<sf::Text>>();

  std::string title_{"Plot"};
  float max_x_value_{0.0};
  float max_y_value_{0.0};
  uint64_t max_x_marker_value_{0};
  uint64_t max_y_marker_value_{0};
  uint64_t min_x_marker_value_{0};
  uint64_t min_y_marker_value_{0};
};

#endif // PLOTINGZ_PLOTTING_DATA_H
