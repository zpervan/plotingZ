#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

TEST(ScatterPlotTest, GivenScatterPlotObject_WhenCreating_ThenScatterPlotObjectSuccessfullyCreated) {
    auto *scatter_plot = new ScatterPlot(new PlottingData);
    ASSERT_TRUE(scatter_plot);
}

class ScatterPlotTestFixture : public ::testing::Test {
protected:
    const std::vector<float> valid_x_data{4.0, 3.0, 2.0, 1.0};
    const std::vector<float> valid_y_data{1.0, 2.0, 3.0, 4.0};

    PlottingData *CreateMockPlottingData() {
        PlottingData *plotting_data{new PlottingData()};
        plotting_data->FindAndSetMaxXValue(valid_x_data);
        plotting_data->FindAndSetMaxYValue(valid_y_data);
        plotting_data->AppendToInputDataValuesCollection(valid_x_data, valid_y_data);
        return plotting_data;
    }
};

TEST_F(ScatterPlotTestFixture,
       DISABLED_GivenValidInputData_WhenVisualizingData_ThenDataPointsAbsolutePositionsAreCorrect) {
    const std::array<sf::Vector2f, 4> expected_data_point_absolute_position{{{600.0, 340.0}, {460.0, 240.0}, {320.0, 140.0}, {180.0, 40.0}}};

    ScatterPlot scatter_plot(CreateMockPlottingData());
    scatter_plot.CreateDataPoints();

    const auto &data_points = scatter_plot.GetPlottingData()->GetDataPointsCollections().front();

    for (std::size_t i{0}; i < valid_x_data.size(); i++) {

        const auto &data_point_x_position = data_points[i].getPosition().x;

        EXPECT_EQ(data_point_x_position, expected_data_point_absolute_position[i].x)
                            << fmt::format("Data point with value XY:{},{} at index {} has X position {}",
                                           valid_x_data[i], valid_y_data[i], i,
                                           data_point_x_position);

        const auto &data_point_y_position = data_points[i].getPosition().y;

        EXPECT_EQ(data_point_y_position, expected_data_point_absolute_position[i].y)
                            << fmt::format("Data point with value XY:{},{} at index {} has Y position {}",
                                           valid_x_data[i], valid_y_data[i], i,
                                           data_point_y_position);;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
