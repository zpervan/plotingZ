#include "Plot/Common/src/plotting_data_builder.h"

PlottingDataBuilder &PlottingDataBuilder::SetMaxXValue(float value) {
  plotting_data.FindAndSetMaxXValue({value});
  return *this;
}

PlottingDataBuilder &PlottingDataBuilder::SetMaxYValue(float value) {
  plotting_data.FindAndSetMaxYValue({value});
  return *this;
}

PlottingDataBuilder &PlottingDataBuilder::SetMaxXMarkerValue(uint64_t value) {
  plotting_data.SetMaxXMarkerValue(value);
  return *this;
}
PlottingDataBuilder &PlottingDataBuilder::SetMaxYMarkerValue(uint64_t value) {
  plotting_data.SetMaxYMarkerValue(value);
  return *this;
}
PlottingDataBuilder &
PlottingDataBuilder::AppendToInputDataValuesCollection(const std::vector<float> &input_data_x,
                                                       const std::vector<float> &input_data_y) {
  plotting_data.AppendToInputDataValuesCollection(input_data_x, input_data_y);
  return *this;
}
PlottingData &PlottingDataBuilder::Build() { return plotting_data; }
