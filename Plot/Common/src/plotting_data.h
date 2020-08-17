#ifndef PLOTINGZ_PLOTTING_DATA_H
#define PLOTINGZ_PLOTTING_DATA_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

/// @todo: Extend plotting of other data types!
/// @todo: Refactor pls...
using InputDataValues = std::pair<std::vector<float>, std::vector<float>>;
using DataPoints = std::vector<sf::CircleShape>;

class PlottingData {
public:
    void SetTitle(const std::string &title);

    void SetAxisShapes(std::vector<sf::RectangleShape> &axis_shapes);

    void SetAxisMarkerValues(std::vector<sf::Text> &axis_marker_values);

    void SetDataPointsCollections(DataPoints &data_points);

    const std::vector<sf::RectangleShape> &GetAxisShapes() const;

    const std::vector<sf::Text> &GetAxisMarkerValues() const;

    float GetMaxXValue() const;

    void SetMaxXValue(const std::vector<float> &x_data);

    float GetMaxYValue() const;

    void SetMaxYValue(const std::vector<float> &y_data);

    const std::vector<DataPoints> &GetDataPointsCollections() const;

    const std::vector<InputDataValues> &GetInputDataValuesCollection() const;

    void AppendToInputDataValuesCollection(const std::vector<float> &input_data_x,
                                           const std::vector<float> &input_data_y);

protected:
    std::unique_ptr<std::vector<InputDataValues>> input_data_values_collection_ = std::make_unique<std::vector<InputDataValues>>();
    std::unique_ptr<std::vector<DataPoints>> data_points_collection_ = std::make_unique<std::vector<DataPoints>>();
    /// @todo: Group into "Axis data"
    std::unique_ptr<std::vector<sf::RectangleShape>> axis_shapes_ = std::make_unique<std::vector<sf::RectangleShape>>();
    std::unique_ptr<std::vector<sf::Text>> axis_marker_values_ = std::make_unique<std::vector<sf::Text>>();
    std::string title_{"Plot"};
    float max_x_value_{0.f};
    float max_y_value_{0.f};

};

#endif //PLOTINGZ_PLOTTING_DATA_H
