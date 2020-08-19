#ifndef PLOTINGZ_MAIN_H
#define PLOTINGZ_MAIN_H

#include "Plot/Common/src/axis.h"
#include "Plot/Common/src/plotting_data.h"
#include "Plot/Common/src/types.h"
#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "Plot/LinePlot/src/line_plot.h"
#include "Plot/Common/src/legend.h"
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

    /// @brief Wrapper function for setting legend labels.
    /// @param labels Labels which represent the meaning for each data points collection
    /// @todo: Try to avoid the wrapper function... Looks-a not very nice!
    void SetLegendLabels(const std::vector<std::string> &labels);

    const PlottingData &GetPlottingData() const;

protected:

    void SetAxis();

    void InitializePlot();

    std::unique_ptr<PlottingData> plotting_data_{std::make_unique<PlottingData>()};
    Legend legend_{plotting_data_.get()};
    Axis axis_{plotting_data_.get()};
    LinePlot line_plot_{};
    ScatterPlot scatter_plot_{};
    PlotType plot_type_;

    bool show_legend{false};
};


#endif //PLOTINGZ_MAIN_H
