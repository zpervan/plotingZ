#ifndef PLOTINGZ_MAIN_H
#define PLOTINGZ_MAIN_H

#include "Plot/Common/src/axis.h"
#include "Plot/Common/src/plotting_data.h"
#include "Plot/Common/src/types.h"
#include "Plot/ScatterPlot/src/scatter_plot.h"
#include <vector>

class PlottingZ {
public:
    void Plot();

    void SetPlotType(PlotType plot_type);

    /// @brief Process given input data and create the data points which will be visualized.
    /// @param [in] input_x_data Input data for X axis
    /// @param [in] input_y_data Input data for Y axis
    void SetData(const std::vector<float> &input_data_x, const std::vector<float> &input_data_y);

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
