#include "Plot/Main/src/main.h"
#include "gtest/gtest.h"

class PlottingZTestFixture : public PlottingZ, public ::testing::Test {
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
};

TEST_F(PlottingZTestFixture, GivenNoInputData_WhenInitializing_ThenExceptionIsThrown) {
    EXPECT_THROW(SetData(empty_x_data, empty_y_data), std::invalid_argument);
}

TEST_F(PlottingZTestFixture, GivenDifferentSizeOfInputData_WhenSettingData_ThenExceptionIsThrown) {
    EXPECT_THROW(SetData(empty_x_data, valid_y_data), std::invalid_argument);
}

TEST_F(PlottingZTestFixture, GivenValidInputData_WhenSettingData_ThenCorrectValuesAreSet) {
    const std::size_t expected_size{4};
    SetData(valid_x_data, valid_y_data);

    const auto &data_points_values_collection = GetPlottingData().GetInputDataValuesCollection();

    const auto &x_data_points = data_points_values_collection.front().first;
    ASSERT_EQ(x_data_points.size(), expected_size);

    const auto &y_data_points = data_points_values_collection.front().second;
    ASSERT_EQ(y_data_points.size(), expected_size);

    CheckDataPoints(x_data_points, valid_x_data);
    CheckDataPoints(y_data_points, valid_y_data);
}

TEST_F(PlottingZTestFixture, GivenValidInputData_WhenSettingData_ThenCorrectMaximumValuesAreSet) {
    const float expected_max_x_value{100.34};
    const float expected_max_y_value{40.91};
    const std::vector<float> x_data{0.0, 3.4, 100.34, 85.1};
    const std::vector<float> y_data{40.91, 11.089, 34.1, 8.51};\

    SetData(x_data, y_data);

    EXPECT_EQ(GetPlottingData().GetMaxXValue(), expected_max_x_value);
    EXPECT_EQ(GetPlottingData().GetMaxYValue(), expected_max_y_value);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}