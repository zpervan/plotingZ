#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

class ScatterPlotTestFixture : public ScatterPlot, public ::testing::Test {
protected:
    const std::vector<float> empty_x_data{};
    const std::vector<float> empty_y_data{};
    const std::vector<float> valid_x_data{4.0, 3.0, 2.0, 1.0};
    const std::vector<float> valid_y_data{1.0, 2.0, 3.0, 4.0};
    const float max_value{4.f};
};

TEST_F(ScatterPlotTestFixture, GivenNoInputData_WhenInitializing_ThenExceptionIsThrown) {
    EXPECT_THROW(SetData(empty_x_data, empty_y_data), std::invalid_argument);
}

TEST_F(ScatterPlotTestFixture, GivenDifferentSizeOfInputData_WhenSettingData_ThenExceptionIsThrown) {
    EXPECT_THROW(SetData(empty_x_data, valid_y_data), std::invalid_argument);
}

TEST_F(ScatterPlotTestFixture, GivenValidInputData_WhenVisualizingData_ThenDataPointsAbsolutePositionsAreCorrect) {
    const std::array<sf::Vector2f, 4> expected_data_point_absolute_position{{{600.0, 340.0}, {460.0, 240.0}, {320.0, 140.0}, {180.0, 40.0}}};

    SetData(valid_x_data, valid_y_data);
    CreateDataPoints();
    const auto &data_points = GetDataPointsCollections().front();

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
