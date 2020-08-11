#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

class ScatterPlotTestFixture : public ScatterPlot, public ::testing::Test {
protected:
    void CheckDataPoints(const std::vector<float> &data_points, const std::vector<float> &expected_data_points) {
        for (std::size_t i{0}; i < expected_data_points.size(); ++i) {
            EXPECT_EQ(data_points[i], expected_data_points[i]);
        }
    }

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

TEST_F(ScatterPlotTestFixture, GivenValidInputData_WhenSettingData_ThenCorrectValuesAreSet) {
    const std::size_t expected_size{4};
    SetData(valid_x_data, valid_y_data);

    const auto &x_data_points = data_points_.front().first;
    ASSERT_EQ(x_data_points.size(), expected_size);

    const auto &y_data_points = data_points_.front().second;
    ASSERT_EQ(y_data_points.size(), expected_size);

    CheckDataPoints(x_data_points, valid_x_data);
    CheckDataPoints(y_data_points, valid_y_data);
}

TEST_F(ScatterPlotTestFixture, GivenValidInputData_WhenSettingData_ThenCorrectMaximumValuesAreSet) {
    const float expected_max_x_value{100.34};
    const float expected_max_y_value{40.91};
    const std::vector<float> x_data{0.0, 3.4, 100.34, 85.1};
    const std::vector<float> y_data{40.91, 11.089, 34.1, 8.51};\

    SetData(x_data, y_data);

    EXPECT_EQ(x_max_element_, expected_max_x_value);
    EXPECT_EQ(y_max_element_, expected_max_y_value);
}


TEST_F(ScatterPlotTestFixture, GivenValidInputData_WhenVisualizingData_ThenDataPointsAbsolutePositionsAreCorrect) {
    const std::array<sf::Vector2f, 4> expected_data_point_absolute_position{{{600.0, 340.0}, {460.0, 240.0}, {320.0, 140.0}, {180.0, 40.0}}};

    SetData(valid_x_data, valid_y_data);
    CreateDataPoints();
    const auto &data_points = data_points_collections_.front();

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
