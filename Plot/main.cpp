#include "Plot/Common/src/config.h"
#include "LinePlot/src/line_plot.h"
#include "ScatterPlot/src/scatter_plot.h"

int main() {

//    LinePlot line_plot;
//    line_plot.Plot();

    std::vector<float> x{1.5, 2.1, 3.3, 4.1, 3.9, 2.8, 7.5};
    std::vector<float> y{6.3, 6.1, 5.56, 4.58, 3.91, 2.63, 1};
    std::vector<float> x1{4.8, 1.2, 3.58, 0.5, 2.63, 9.91, 1};
    std::vector<float> y1{8.3, 2.1, 9.56, 0.58, 2.91, 4.63, 2};

    std::vector<float> x2{1.8, 3.2, 6.58, 1.5, 0.63, 2.91, 0};
    std::vector<float> y2{1.3, 7.1, 4.56, 0.58, 5.91, 3.63, 1};

    ScatterPlot scatter_plot;
    scatter_plot.SetData(x, y);
    scatter_plot.SetData(x1, y1);
    scatter_plot.SetData(x2, y2);
    scatter_plot.Plot();
    return 0;
}
