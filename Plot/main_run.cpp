#include "Plot/Main/src/main.h"
#include "Plot/Utility/src/input_data_utility.h"

int main() {
  // Create a plottingZ object instance
  PlottingZ plottingZ;

  // Set the plot type to line plot
  //  plottingZ.SetPlotType(PlotType::LinePlot);

  // Set the plot type to scatter plot
  plottingZ.SetPlotType(PlotType::ScatterPlot);

  // Create some dummy data
  const auto &[time, sin] = InputData::GenerateSineWave({});
  plottingZ.SetData(time, sin);

  const auto &[time2, sin2] = InputData::GenerateSineWave({1.0, 0.5, 1.0, 0.0125, 200});
  plottingZ.SetData(time2, sin2);

  // Create a legend and give the data some names
  plottingZ.SetLegendLabels({"Black sinus", "Red sinus"});

  // Plot the data!
  plottingZ.Plot();
  return 0;
}
