#ifndef PLOTINGZ_SCATTER_PLOT_H
#define PLOTINGZ_SCATTER_PLOT_H

#include "Plot/Common/src/axis.h"

/// @todo: Extend plotting of other data types!
using XYData = std::pair<std::vector<float>, std::vector<float>>;

class ScatterPlot : private Axis {
public:
    void Plot();

    void SetData(const std::vector<float> &x_data, const std::vector<float> &y_data);

    void SetTitle(const std::string &title);

protected:

    void SetAxis();

    void CreateDataPoints();

    void SetMaxXElement(const std::vector<float> &x_data);

    void SetMaxYElement(const std::vector<float> &y_data);

    sf::CircleShape CreateCircleDataPointSkeleton();

    std::vector<std::vector<sf::CircleShape>> data_points_collections_{};
    std::vector<XYData> data_points_{};

    std::string title_{"Scatter Plot"};

    float x_max_element_{0.f};
    float y_max_element_{0.f};
    std::size_t color_count_{0};
};


#endif //PLOTINGZ_SCATTER_PLOT_H
