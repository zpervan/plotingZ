#ifndef PLOTINGZ_LEGEND_H
#define PLOTINGZ_LEGEND_H

#include "Plot/Common/src/config.h"
#include "Plot/Common/src/plotting_data.h"


class Legend {
public:
    explicit Legend(PlottingData *plotting_data) : plotting_data_(plotting_data) {};

    Legend() = default;

    ~Legend() = default;

    /// @todo: For every XY data, there should be a entry in the legend, also, the appropriate colour is used for each data point
    void SetLegendLabels(const std::vector<std::string> &labels);

    void CreateLegend();

    const std::vector<std::string> &GetLabels() const;


protected:
    std::vector<sf::RectangleShape> CreateLabelBoxes();

    std::vector<sf::Text> CreateLabelText();

    sf::RectangleShape CreateLegendFrame();

    std::vector<std::string> labels_;

    PlottingData *plotting_data_;
};

#endif //PLOTINGZ_LEGEND_H
