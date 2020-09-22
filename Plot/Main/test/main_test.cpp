#include "Plot/Main/src/main.h"
#include "gtest/gtest.h"

class PlottingZTestFixture : public ::testing::Test {
protected:
    void CheckDataPoints(const std::vector<sf::Vector2f> &data_points,
                         const std::vector<sf::Vector2f> &expected_data_points) {
        for (std::size_t i{0}; i < expected_data_points.size(); ++i) {
            EXPECT_EQ(data_points[i].x, expected_data_points[i].x);
            EXPECT_EQ(data_points[i].y, expected_data_points[i].y);
        }
    }

    PlottingZ plottingZ{};
    const std::vector<float> empty_x_data{};
    const std::vector<float> empty_y_data{};
    const std::vector<float> valid_x_data{4.0, 3.0, 2.0, 1.0};
    const std::vector<float> valid_y_data{1.0, 2.0, 3.0, 4.0};
    const std::vector<sf::Vector2f> valid_data_points{{4.0, 1.0},
                                                      {3.0, 2.0},
                                                      {2.0, 3.0},
                                                      {1.0, 4.0}};
};

TEST_F(PlottingZTestFixture, GivenNoInputData_WhenInitializing_ThenExceptionIsThrown) {
    EXPECT_THROW(plottingZ.SetData(empty_x_data, empty_y_data), std::invalid_argument);
}

TEST_F(PlottingZTestFixture, GivenDifferentSizeOfInputData_WhenSettingData_ThenExceptionIsThrown) {
    EXPECT_THROW(plottingZ.SetData(empty_x_data, valid_y_data), std::invalid_argument);
}

TEST_F(PlottingZTestFixture, GivenPlotTypeNotSet_WhenPlottingData_ThenExceptionIsThrown) {
    EXPECT_THROW(plottingZ.Plot(), std::invalid_argument);
}

TEST_F(PlottingZTestFixture, GivenValidInputData_WhenSettingData_ThenCorrectValuesAreSet) {
    const std::size_t expected_values_collection_size{1};
    const std::size_t expected_data_points_size{4};

    plottingZ.SetData(valid_x_data, valid_y_data);

    const auto &data_points_values_collection = plottingZ.GetPlottingData().GetInputDataValuesCollection();
    ASSERT_EQ(data_points_values_collection.size(), expected_values_collection_size);

    const auto &data_points = data_points_values_collection.front();
    ASSERT_EQ(data_points.size(), expected_data_points_size);

    CheckDataPoints(data_points, valid_data_points);
}

TEST_F(PlottingZTestFixture, GivenValidInputData_WhenSettingData_ThenCorrectMaximumValuesAreSet) {
    const float expected_max_x_value{100.34};
    const float expected_max_y_value{40.91};
    const std::vector<float> x_data{0.0, 3.4, 100.34, 85.1};
    const std::vector<float> y_data{40.91, 11.089, 34.1, 8.51};

    plottingZ.SetData(x_data, y_data);

    EXPECT_EQ(plottingZ.GetPlottingData().GetMaxXValue(), expected_max_x_value);
    EXPECT_EQ(plottingZ.GetPlottingData().GetMaxYValue(), expected_max_y_value);
}

TEST_F(PlottingZTestFixture, GivenLabelData_WhenSettingLegendLabelData_ThenLabelDataIsShown) {
    const std::size_t expected_legend_label_size{3};
    const std::vector<std::string> legend_labels{"Cool", "Data", "Bruh"};
    plottingZ.SetLegendLabels(legend_labels);

    ASSERT_EQ(legend_labels.size(), expected_legend_label_size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
