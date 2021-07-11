#include "Plot/Common/src/plotting_data_builder.h"

#include "gtest/gtest.h"

TEST(PlottingDataBuilderTest,
     GivenValidData_WhenCreatingPlottingDataMock_ThenPlottingDataMockFilledWithCorrectData) {
  PlottingDataBuilder plotting_data_builder;
  PlottingData plotting_data =
      std::move(plotting_data_builder.SetMaxXValue(10.0)
                    .SetMaxYValue(20.0)
                    .SetMaxXMarkerValue(30)
                    .SetMaxYMarkerValue(40)
                    .AppendToInputDataValuesCollection({1.0, 2.0, 3.0}, {4.0, 5.0, 6.0})
                    .Build());
  constexpr float expected_max_x_value{10.0};
  EXPECT_EQ(plotting_data.GetMaxXValue(), expected_max_x_value);

  constexpr float expected_max_y_value{20.0};
  EXPECT_EQ(plotting_data.GetMaxYValue(), expected_max_y_value);

  constexpr uint64_t expected_max_x_marker_value{30};
  EXPECT_EQ(plotting_data.GetMaxXMarkerValue(), expected_max_x_marker_value);

  constexpr uint64_t expected_max_y_marker_value{40};
  EXPECT_EQ(plotting_data.GetMaxYMarkerValue(), expected_max_y_marker_value);

  constexpr std::size_t expected_mock_input_data_value_collection_size{1};
  ASSERT_EQ(plotting_data.GetInputDataValuesCollection().size(),
            expected_mock_input_data_value_collection_size);

  constexpr std::size_t expected_mock_input_data_values_size{3};
  const auto &actual_input_data_values{plotting_data.GetInputDataValuesCollection().back()};
  ASSERT_EQ(actual_input_data_values.size(), expected_mock_input_data_values_size);

  const std::array<sf::Vector2f, 3> expected_input_data_values{{{1.0, 4.0}, {2.0, 5.0}, {3.0, 6.0}}};
  for (std::size_t i{0}; i < actual_input_data_values.size(); ++i) {
    EXPECT_EQ(actual_input_data_values[i].x, expected_input_data_values[i].x);
    EXPECT_EQ(actual_input_data_values[i].y, expected_input_data_values[i].y);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}