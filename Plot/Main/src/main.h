#ifndef PLOTINGZ_MAIN_H
#define PLOTINGZ_MAIN_H

#include "Plot/Common/src/axis.h"
#include "Plot/Common/src/plotting_data.h"
#include "Plot/Common/src/types.h"
#include "Plot/ScatterPlot/src/scatter_plot.h"
#include <vector>

class PlottingZ {
public:
    /// @brief Sets the raw input data.
    /// @param [in] input_x_data Raw input data X
    /// @param [in] input_y_data Input data for Y
    void SetData(const std::vector<float> &input_data_x, const std::vector<float> &input_data_y);

    /// @brief Sets the type of plot which will be shown. Default plot type - scatter plot.
    /// @param [in] plot_type Type of plot which will be visualized
    void SetPlotType(PlotType plot_type);

    /// @brief Plots the processed data.
    void Plot();

    const PlottingData &GetPlottingData() const;

private:

    void SetAxis();

    PlotType plot_type_;
    PlottingData plotting_data_{};
//    Axis axis_{plotting_data_};
//    ScatterPlot scatter_plot_{};
//    LinePlot line_plot_{};
};


#endif //PLOTINGZ_MAIN_H
