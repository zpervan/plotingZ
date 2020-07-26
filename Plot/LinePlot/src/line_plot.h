#ifndef PLOTINGZ_LINE_PLOT_H
#define PLOTINGZ_LINE_PLOT_H

#include "Plot/Common/src/axis.h"

#include "include/SFML/Graphics.hpp"
#include <cstddef>
#include <vector>

class LinePlot : public Axis {
public:
    LinePlot() = default;

    ~LinePlot() = default;

    void SetData(const std::vector<int> &data);

    void Plot(const std::string &title = "Line plot");

private:
    void DrawGrid();

    std::vector<int> data_{};
    bool draw_grid{true};
};


#endif //PLOTINGZ_LINE_PLOT_H
