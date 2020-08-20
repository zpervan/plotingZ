#ifndef PLOTINGZ_PLOTTING_DATA_H
#define PLOTINGZ_PLOTTING_DATA_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

/// @todo: Extend plotting of other data types! Is this needed?
using InputDataValues = std::pair<std::vector<float>, std::vector<float>>;
using DataPoints = std::vector<sf::CircleShape>;
using DataLines = std::vector<sf::RectangleShape>;

/// @brief Serves as a central data container for raw and processed data. This data will be used for visualization.
class PlottingData {
public:
    /// @brief Pairs and appends the raw input data to a vector.
    /// @param [in] input_data_x Raw input data X
    /// @param [in] input_data_y Raw input data Y
    void AppendToInputDataValuesCollection(const std::vector<float> &input_data_x,
                                           const std::vector<float> &input_data_y);

    /// @brief Finds and sets the maximum value (if possible) for given input data X.
    /// @param [in] input_data_x Raw input data X
    void FindAndSetMaxXValue(const std::vector<float> &input_data_x);

    /// @brief Finds and sets the maximum value (if possible) for given input data Y.
    /// @param [in] input_data_y Raw input data Y
    void FindAndSetMaxYValue(const std::vector<float> &input_data_y);

    /// @brief Adds new data points to a vector.
    /// @param [in] data_points Processed circle shaped data
    void EmplaceDataPointsCollections(DataPoints &data_points);

    /// @section Setters

    void SetAxisShapes(std::vector<sf::RectangleShape> &axis_shapes);

    void SetAxisMarkerValues(std::vector<sf::Text> &axis_marker_values);

    void SetLegendShapes(std::vector<sf::RectangleShape> &legend_shapes);

    void SetLegendLabels(std::vector<sf::Text> &legend_labels);

    void SetTitle(const std::string &title);

    /// @section Getters

    const std::vector<sf::RectangleShape> &GetAxisShapes() const;

    const std::vector<sf::Text> &GetAxisMarkerValues() const;

    const std::vector<sf::RectangleShape> &GetLegendShapes() const;

    const std::vector<sf::Text> &GetLegendLabelTexts() const;

    float GetMaxXValue() const;

    float GetMaxYValue() const;

    const std::vector<DataPoints> &GetDataPointsCollections() const;

    const std::vector<InputDataValues> &GetInputDataValuesCollection() const;

protected:
    std::unique_ptr<std::vector<InputDataValues>> input_data_values_collection_ = std::make_unique<std::vector<InputDataValues>>();
    std::unique_ptr<std::vector<DataPoints>> data_points_collection_ = std::make_unique<std::vector<DataPoints>>();
    /// @todo: Group into "Axis data"
    std::unique_ptr<std::vector<sf::RectangleShape>> axis_shapes_ = std::make_unique<std::vector<sf::RectangleShape>>();
    std::unique_ptr<std::vector<sf::Text>> axis_marker_values_ = std::make_unique<std::vector<sf::Text>>();
    std::unique_ptr<std::vector<sf::RectangleShape>> legend_shapes_ = std::make_unique<std::vector<sf::RectangleShape>>();
    std::unique_ptr<std::vector<sf::Text>> legend_labels_ = std::make_unique<std::vector<sf::Text>>();
    std::string title_{"Plot"};
    float max_x_value_{0.f};
    float max_y_value_{0.f};

};

#endif //PLOTINGZ_PLOTTING_DATA_H
