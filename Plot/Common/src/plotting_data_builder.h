#ifndef PLOTINGZ_PLOT_COMMON_SRC_PLOTTING_DATA_BUILDER_H_
#define PLOTINGZ_PLOT_COMMON_SRC_PLOTTING_DATA_BUILDER_H_

#include "Plot/Common/src/plotting_data.h"

class PlottingDataBuilder {
public:
  PlottingDataBuilder &SetMaxXValue(float value);
  PlottingDataBuilder &SetMaxYValue(float value);
  PlottingDataBuilder &SetMaxXMarkerValue(uint64_t value);
  PlottingDataBuilder &SetMaxYMarkerValue(uint64_t value);
  PlottingDataBuilder &AppendToInputDataValuesCollection(const std::vector<float> &input_data_x,
                                                         const std::vector<float> &input_data_y);
  [[nodiscard]] PlottingData &Build();

private:
  PlottingData plotting_data;
};

#endif // PLOTINGZ_PLOT_COMMON_SRC_PLOTTING_DATA_BUILDER_H_
