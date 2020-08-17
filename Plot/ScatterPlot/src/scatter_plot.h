#ifndef PLOTINGZ_SCATTER_PLOT_H
#define PLOTINGZ_SCATTER_PLOT_H

#include "Plot/Common/src/axis.h"
#include "Plot/Common/src/plotting_data.h"


/// @brief This class contains the logic visualizing input in the form of points/dots/circles.
class ScatterPlot {
public:
    ScatterPlot(PlottingData* plotting_data) : plotting_data_(plotting_data) {};

    ScatterPlot() = default;

    ~ScatterPlot() = default;

    void CreateDataPoints();

    PlottingData *GetPlottingData() const;
protected:

    sf::CircleShape CreateCircleDataPointSkeleton();
    PlottingData* plotting_data_{nullptr};
    std::size_t color_count_{0};
};


#endif //PLOTINGZ_SCATTER_PLOT_H
