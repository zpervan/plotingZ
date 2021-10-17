#include "Plot/LinePlot/src/line_plot.h"
#include "ThirdParty/fmt/include/fmt/format.h"

#include "gtest/gtest.h"

#include <array>

class LinePlotTestFixture : public ::testing::Test {
protected:
  const std::vector<float> valid_x_data{1.0, 2.0, 3.0, 4.0};
  const std::vector<float> valid_y_data{4.0, 3.0, 2.0, 1.0};

  PlottingData *CreatePlottingDataMock() {
    PlottingData *plotting_data{new PlottingData()};
    plotting_data->FindAndSetMaxXValue(valid_x_data);
    plotting_data->FindAndSetMaxYValue(valid_y_data);
    plotting_data->SetMaxXMarkerValue(5);
    plotting_data->SetMaxYMarkerValue(5);
    plotting_data->AppendToInputDataValuesCollection(valid_x_data, valid_y_data);
    return plotting_data;
  }
};

TEST_F(LinePlotTestFixture, GivenValidInputData_WhenCreatingLinePlot_ThenLineDataValuesPositionsAreCorrect) {
  const std::size_t expected_line_data_values_size{3};
  const std::array<sf::Vector2f, 3> expected_data_point_positions{
      {{176.0, 112.0}, {288.0, 192.0}, {400.0, 272.0}}};

  PlottingData *plotting_data_mock = CreatePlottingDataMock();
  LinePlot line_plot{plotting_data_mock};
  line_plot.CreateLinePlot();

  const auto &line_data_values = plotting_data_mock->GetLineDataValueCollection().front();

  ASSERT_EQ(line_data_values.size(), expected_line_data_values_size);

  for (std::size_t i{0}; i < line_data_values.size(); i++) {
    const auto &actual_plot_line_position = line_data_values[i].getPosition();

    EXPECT_FLOAT_EQ(actual_plot_line_position.x, expected_data_point_positions.at(i).x)
        << fmt::format("Test case {} failed with X value {}", i, valid_y_data.at(i));
    EXPECT_FLOAT_EQ(actual_plot_line_position.y, expected_data_point_positions.at(i).y)
        << fmt::format("Test case {} failed with Y value {}", i, valid_y_data.at(i));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
