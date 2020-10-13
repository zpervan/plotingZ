#include "Plot/Main/src/main.h"
#include <cmath>

using SineData = std::pair<std::vector<float>, std::vector<float>>;

SineData CreateSineWave(double sample) {
  std::vector<float> sin;
  std::vector<float> time;
  double value{0.0};
  for (std::size_t i{0}; i <= 125; i++) {
	value += sample;
	sin.emplace_back(2 * std::sin(value) + 2);
	time.emplace_back(i);
  }
  return {time, sin};
}

int main() {
  // Create a plottingZ object instance
  PlottingZ plottingZ;

  // Set the plot type to line plot
  plottingZ.SetPlotType(PlotType::LinePlot);

  // Set the plot type to scatter plot
//  plottingZ.SetPlotType(PlotType::ScatterPlot);

  // Create some dummy data
  const auto&[time, sin] = CreateSineWave(0.1);
  plottingZ.SetData(time, sin);

  const auto&[time2, sin2] = CreateSineWave(0.05);
  plottingZ.SetData(time2, sin2);

  const auto&[time3, sin3] = CreateSineWave(0.025);
  plottingZ.SetData(time3, sin3);

  // Create a legend and give the data some names
  plottingZ.SetLegendLabels({"Black sinus", "Red sinus", "Green sinus"});

  // Plot the data!
  plottingZ.Plot();
  return 0;
}
