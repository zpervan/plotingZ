#ifndef PLOTINGZ_LINE_PLOT_H
#define PLOTINGZ_LINE_PLOT_H

#include "Plot/Common/src/axis.h"

#include <cstddef>
#include <vector>

class LinePlot {
public:
    void SetData(const std::vector<int> &data);

    void Plot(const std::string &title = "Line plot");
private:
    Axis axis_;
    std::vector<int> data_{};
//    bool draw_grid{true};
};

#endif //PLOTINGZ_LINE_PLOT_H
