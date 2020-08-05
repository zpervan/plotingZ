#include "Plot/Common/src/config.h"
#include "LinePlot/src/line_plot.h"
#include "ScatterPlot/src/scatter_plot.h"

int main() {

//    LinePlot line_plot;
//    line_plot.Plot();

    std::vector<float> x{1, 2, 3, 4, 5, 6, 7};
    std::vector<float> y{7, 6, 5, 4, 3, 2, 1};

    ScatterPlot scatter_plot;
    scatter_plot.SetData(x, y);
    scatter_plot.Plot();
    return 0;
}
