#include "Plot/Common/src/config.h"
#include "Plot/Main/src/main.h"

int main() {

    std::vector<float> x{1.5, 2.1, 3.3, 4.1, 3.9, 2.8, 7.5};
    std::vector<float> y{6.3, 6.1, 5.56, 4.58, 3.91, 2.63, 1};
    std::vector<float> x1{4.8, 1.2, 3.58, 0.5, 2.63, 9.91, 1};
    std::vector<float> y1{8.3, 2.1, 9.56, 0.58, 2.91, 4.63, 2};

    std::vector<float> x2{1.8, 3.2, 6.58, 1.5, 0.63, 2.91, 0};
    std::vector<float> y2{1.3, 7.1, 4.56, 0.58, 5.91, 3.63, 1};

    const std::vector<float> valid_x_data{4.0, 3.0, 2.0, 1.0};
    const std::vector<float> valid_y_data{1.0, 2.0, 3.0, 4.0};

    PlottingZ plottingZ;
    plottingZ.SetData(x, y);
    plottingZ.SetData(x1, y1);
    plottingZ.SetData(x2, y2);
    plottingZ.SetData(valid_x_data, valid_y_data);
//    plottingZ.Plot();
    return 0;
}
