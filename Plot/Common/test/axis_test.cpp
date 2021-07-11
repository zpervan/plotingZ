#include "Plot/Common/src/axis.h"
#include "ThirdParty/fmt/include/fmt/core.h"

#include "gtest/gtest.h"

/// @todo: Axis should have a protected constructor which takes a custom config for window height and width,
/// otherwise the test will fail if we change the window size in the config file

class AxisTestFixture : public ::testing::Test {
protected:
  const std::vector<float> valid_x_data{14.28, 3.0, 2.0, 0.021};
  const std::vector<float> valid_y_data{0.98, 2.0, 3.0, 13.13};
  const double tolerance{1e-3};

  PlottingData *CreatePlottingDataMock() {
    PlottingData *plotting_data{new PlottingData()};
    plotting_data->FindAndSetMaxXValue(valid_x_data);
    plotting_data->FindAndSetMaxYValue(valid_y_data);
    return plotting_data;
  }
};

TEST_F(AxisTestFixture, GivenInputValuesAreSet_WhenAxisCreated_ThenNumberOfAxisShapesIsCorrect) {
  constexpr std::size_t expected_axis_shape_size{10};

  PlottingData *plotting_data_mock = CreatePlottingDataMock();

  std::optional<Axis> axis{plotting_data_mock};
  axis->CreateAxis();

  ASSERT_TRUE(axis.has_value()) << fmt::format("Axis object failed to initialize!");
  ASSERT_EQ(plotting_data_mock->GetAxisShapes().size(), expected_axis_shape_size);
}

TEST_F(AxisTestFixture, GivenInputValuesAreSet_WhenAxisShapesCreated_ThenAxisShapePositionsAreCorrect) {
  constexpr std::size_t expected_number_of_shape_elements{10};
  const std::array<sf::Vector2f, 10> expected_axis_shape_positions{{{64.0, 432.0},
                                                                    {66.0, 432.0},
                                                                    {252.666, 432.0},
                                                                    {439.333, 432.0},
                                                                    {626.0, 432.0},
                                                                    {64.0, 432.0},
                                                                    {64.0, 432.0},
                                                                    {64.0, 298.666},
                                                                    {64.0, 165.333},
                                                                    {64.0, 32.0}}};

  PlottingData *plotting_data_mock = CreatePlottingDataMock();

  Axis axis{plotting_data_mock};
  axis.CreateAxis();

  ASSERT_EQ(plotting_data_mock->GetAxisShapes().size(), expected_number_of_shape_elements);

  for (std::size_t i{0}; i < expected_axis_shape_positions.size(); i++) {
    EXPECT_NEAR(plotting_data_mock->GetAxisShapes()[i].getPosition().x, expected_axis_shape_positions[i].x,
                tolerance)
        << fmt::format("X at shape element with index {}", i);

    EXPECT_NEAR(plotting_data_mock->GetAxisShapes()[i].getPosition().y, expected_axis_shape_positions[i].y,
                tolerance)
        << fmt::format("Y at shape element with index {}", i);
  }
}

TEST_F(AxisTestFixture,
       GivenInputValuesAreSet_WhenCreatingAxisMarkerValues_ThenCorrectAxisMarkerValuesCreated) {
  constexpr std::size_t expected_axis_value_size{8};

  PlottingData *plotting_data_mock = CreatePlottingDataMock();

  std::optional<Axis> axis{plotting_data_mock};
  axis->CreateAxis();

  ASSERT_EQ(plotting_data_mock->GetAxisMarkerValues().size(), expected_axis_value_size);
}

/// @todo: Marker value shape test
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
