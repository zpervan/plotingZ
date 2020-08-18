#ifndef PLOTINGZ_LEGEND_H
#define PLOTINGZ_LEGEND_H

#include "Plot/Common/src/config.h"


class Legend {
public:
    /// @todo: For every XY data, there should be a entry in the legend, also, the appropriate colour is used for each data point
    void SetLegendLabels(const std::vector<std::string> &labels);

    void CreateLegend();

protected:
    std::vector<sf::RectangleShape> CreateLabelBoxes();

    std::vector<sf::Font> CreateLabelText();

    sf::RectangleShape CreateLegendFrame();

    std::vector<std::string> labels_;

};

#endif //PLOTINGZ_LEGEND_H
