#include "Plot/ScatterPlot/src/scatter_plot.h"
#include "ThirdParty/fmt/include/fmt/core.h"
#include "gtest/gtest.h"

class ScatterPlotTestFixture : public ::testing::Test {
 protected:
  const std::vector<float> valid_x_data{4.0, 3.0, 2.0, 1.0};
  const std::vector<float> valid_y_data{1.0, 2.0, 3.0, 4.0};

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
};

TEST_F(ScatterPlotTestFixture,
	   GivenValidInputData_WhenCreatingLinePlot_ThenPointDataPositionsAreCorrect) {
  const std::size_t expected_point_data_collection_size{4};
  const std::array<sf::Vector2f, 4> expected_point_data_position{{{600.0, 340.0},
																  {460.0, 240.0},
																  {320.0, 140.0},
																  {180.0, 40.0}}};

  PlottingData *plotting_data = CreatePlottingDataMock();
  ScatterPlot scatter_plot(plotting_data);
  scatter_plot.CreateScatterPlot();

  const auto &point_data_collection = plotting_data->GetDataPointsCollection().front();
  ASSERT_EQ(point_data_collection.size(), expected_point_data_collection_size);

  for (std::size_t i{0}; i < valid_x_data.size(); i++) {
	const auto &actual_point_data_position = point_data_collection[i].getPosition();

	EXPECT_EQ(actual_point_data_position.x, expected_point_data_position[i].x)
			  << PrintTestPointDataInformation(i, valid_x_data[i], valid_y_data[i]);
	EXPECT_EQ(actual_point_data_position.y, expected_point_data_position[i].y)
			  << PrintTestPointDataInformation(i, valid_x_data[i], valid_y_data[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
