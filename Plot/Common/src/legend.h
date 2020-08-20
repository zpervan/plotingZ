#ifndef PLOTINGZ_LEGEND_H
#define PLOTINGZ_LEGEND_H

#include "Plot/Common/src/config.h"
#include "Plot/Common/src/plotting_data.h"

/// @todo: Legend frame should be non-transparent
class Legend {
public:
    explicit Legend(PlottingData *plotting_data) : plotting_data_(plotting_data) {};

    Legend() = default;

    ~Legend() = default;

    /// @brief Set the text/name for the legend labels
    /// @param labels Texts/names for given data
    void SetLegendLabels(const std::vector<std::string> &labels);

    /// @brief Creates the legend with names for each label
    void CreateLegend();

    const std::vector<std::string> &GetLabels() const;

protected:
    std::vector<sf::RectangleShape> CreateLabelBoxes();

    std::vector<sf::Text> CreateLabelText();

    sf::RectangleShape CreateLegendFrame();

    std::vector<std::string> labels_{};
    PlottingData *plotting_data_{nullptr};
};

#endif //PLOTINGZ_LEGEND_H
