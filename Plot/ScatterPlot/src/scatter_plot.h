#ifndef PLOTINGZ_SCATTER_PLOT_H
#define PLOTINGZ_SCATTER_PLOT_H

#include "Plot/Common/src/axis.h"
#include "Plot/Common/src/plotting_data.h"


/// @brief Contains the logic for converting input data to points/dots/circle shapes.
class ScatterPlot {
public:
    explicit ScatterPlot(PlottingData *plotting_data) : plotting_data_(plotting_data) {};

    ScatterPlot(const ScatterPlot &source);

    ScatterPlot &operator=(const ScatterPlot &rhs);

    ScatterPlot() = default;

    ~ScatterPlot() = default;

    ScatterPlot(ScatterPlot &&source) noexcept;

    ScatterPlot &operator=(ScatterPlot &&rhs) noexcept;

    /// @brief Creates data points from given raw input data.
    void CreateDataPoints();

    PlottingData *GetPlottingData() const;

protected:

    sf::CircleShape CreateCircleDataPointSkeleton();

    PlottingData *plotting_data_{nullptr};
    std::size_t color_count_{0};
};


#endif //PLOTINGZ_SCATTER_PLOT_H
