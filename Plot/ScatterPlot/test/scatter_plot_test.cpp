#include "Plot/ScatterPlot/src/scatter_plot.h"

#include "gtest/gtest.h"

TEST(ScatterPlotTest, GivenNoInputData_WhenInitializing_ThenExceptionIsThrown) {
    ScatterPlot scatter_plot;
    EXPECT_THROW(scatter_plot.Plot(), std::invalid_argument);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
