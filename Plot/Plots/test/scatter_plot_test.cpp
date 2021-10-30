#include "Plot/Plots/src/scatter_plot.h"

#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

#include <array>

class ScatterPlotTestFixture : public ::testing::Test {
 protected:
  const std::vector<float> valid_x_data{0.0, 4.0, 3.0, 2.0, 1.0};
  const std::vector<float> valid_y_data{0.0, 1.0, 2.0, 3.0, 4.0};

  PlottingData *CreatePlottingDataMock() {
	PlottingData *plotting_data{new PlottingData()};
	plotting_data->SetMaxXMarkerValue(4.0);
	plotting_data->SetMaxYMarkerValue(4.0);
	plotting_data->AppendToInputDataValuesCollection(valid_x_data, valid_y_data);
	return plotting_data;
  }

  std::string PrintTestPointDataInformation(std::size_t index, float x, float y) {
	return fmt::format("Test case {} with X:{},Y:{} failed.", index, valid_x_data[index], valid_y_data[index]);
  }

  const double tolerance{1e-1};
};

TEST_F(ScatterPlotTestFixture,
	   GivenValidInputData_WhenCreatingScatterPlot_ThenPointDataPositionsAreCorrect) {
  const std::size_t expected_point_data_collection_size{5};
  const std::array<sf::Vector2f, 5> expected_point_data_position{{{63.0, 429.5},
																  {623.0, 329.5},
																  {483.0, 229.5},
																  {343.0, 129.5},
																  {203.0, 29.5}}};

  PlottingData *plotting_data = CreatePlottingDataMock();
  ScatterPlot scatter_plot(plotting_data);
  scatter_plot.CreateScatterPlot();

  const auto &point_data_collection = plotting_data->GetPointDataCollection().front();
  ASSERT_EQ(point_data_collection.size(), expected_point_data_collection_size);

  for (std::size_t i{0}; i < valid_x_data.size(); i++) {
	const auto &actual_point_data_position = point_data_collection[i].getPosition();

	EXPECT_NEAR(actual_point_data_position.x, expected_point_data_position[i].x, tolerance)
			  << PrintTestPointDataInformation(i, valid_x_data[i], valid_y_data[i]);
	EXPECT_NEAR(actual_point_data_position.y, expected_point_data_position[i].y, tolerance)
			  << PrintTestPointDataInformation(i, valid_x_data[i], valid_y_data[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
