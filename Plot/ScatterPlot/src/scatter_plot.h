#ifndef PLOTINGZ_SCATTER_PLOT_H
#define PLOTINGZ_SCATTER_PLOT_H

#include "Plot/Common/src/axis.h"

/// @todo: Extend plotting of other data types!
class ScatterPlot : private Axis {
public:
    void Plot();

    void SetData(const std::vector<float> &x_data, const std::vector<float> &y_data);

    void SetTitle(const std::string &title);

    const std::vector<float> &GetXData() const;

    const std::vector<float> &GetYData() const;

    const std::vector<sf::CircleShape> &GetDataPoints() const;

private:
    const float MaxElement(const std::vector<float> &elements);

    void CreateDataPoints();

    std::vector<sf::CircleShape> data_points_{};

    std::vector<float> x_data_{};
    std::vector<float> y_data_{};
    std::string title_{"Scatter Plot"};
    float x_max_element_{0};
    float y_max_element_{0};
};


#endif //PLOTINGZ_SCATTER_PLOT_H
