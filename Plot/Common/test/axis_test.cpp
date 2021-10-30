#include "Plot/Common/src/axis.h"

#include <array>
#include <optional>

#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

/// @todo: Axis should have a protected constructor which takes a custom config for window height and width,
/// otherwise the test will fail if we change the window size in the config file

class AxisTestFixture : public ::testing::Test
{
  protected:
    const std::vector<float> valid_x_data{14.28, 3.0, 2.0, 0.021};
    const std::vector<float> valid_y_data{0.98, 2.0, 3.0, 13.13};
    const double tolerance{1e-3};

    PlottingData* CreatePlottingDataMock()
    {
        PlottingData* plotting_data{new PlottingData()};
        plotting_data->FindAndSetMaxXValue(valid_x_data);
        plotting_data->FindAndSetMaxYValue(valid_y_data);
        return plotting_data;
    }
};

TEST_F(AxisTestFixture, GivenInputValuesAreSet_WhenAxisCreated_ThenNumberOfAxisShapesIsCorrect)
{
    constexpr std::size_t expected_axis_shape_size{10};

    PlottingData* plotting_data_mock = CreatePlottingDataMock();

    std::optional<Axis> axis{plotting_data_mock};
    axis->CreateAxis();

    ASSERT_TRUE(axis.has_value()) << fmt::format("Axis object failed to initialize!");
    ASSERT_EQ(plotting_data_mock->GetAxisShapes().size(), expected_axis_shape_size);
}

TEST_F(AxisTestFixture, GivenInputValuesAreSet_WhenAxisShapesCreated_ThenNumberOfAxisShapeCreated)
{
    constexpr std::size_t expected_number_of_shape_elements{10};

    PlottingData* plotting_data_mock = CreatePlottingDataMock();

    Axis axis{plotting_data_mock};
    axis.CreateAxis();

    ASSERT_EQ(plotting_data_mock->GetAxisShapes().size(), expected_number_of_shape_elements);
}

TEST_F(AxisTestFixture, GivenInputValuesAreSet_WhenCreatingAxisMarkerValues_ThenCorrectAxisMarkerValuesCreated)
{
    constexpr std::size_t expected_axis_value_size{8};

    PlottingData* plotting_data_mock = CreatePlottingDataMock();

    std::optional<Axis> axis{plotting_data_mock};
    axis->CreateAxis();

    ASSERT_EQ(plotting_data_mock->GetAxisMarkerValues().size(), expected_axis_value_size);
}

/// @todo: Marker value shape test
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
