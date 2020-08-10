#include "Plot/ScatterPlot/src/scatter_plot.h"

#include "gtest/gtest.h"

TEST(ScatterPlotTest, GivenNoInputData_WhenInitializing_ThenExceptionIsThrown) {
    const std::vector<float> empty_x_data{};
    const std::vector<float> empty_y_data{};

    ScatterPlot scatter_plot;
    EXPECT_THROW(scatter_plot.SetData(empty_x_data, empty_y_data), std::invalid_argument);
}

TEST(ScatterPlotTest, GivenDifferentSizeOfInputData_WhenSettingData_ThenExceptionIsThrown) {
    const std::vector<float> x_data{};
    const std::vector<float> y_data{0.0};

    ScatterPlot scatter_plot;

    EXPECT_THROW(scatter_plot.SetData(x_data, y_data), std::invalid_argument);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
