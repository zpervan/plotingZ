#ifndef PLOTINGZ_PLOT_UTILITY_SRC_INPUT_DATA_UTILITY_H_
#define PLOTINGZ_PLOT_UTILITY_SRC_INPUT_DATA_UTILITY_H_

#include <vector>

using SineData = std::pair<std::vector<float>, std::vector<float>>;

namespace InputData {

struct WaveformParameters {
  float amplitude{1.0};
  float phase_shift{0.0};
  float vertical_shift{1.0};
  float sample_rate{0.0125};
  std::size_t duration{200};
};

/// @brief
/// @param[in] sample_rate
/// @return
SineData GenerateSineWave(const WaveformParameters &parameters);

} // namespace InputData

#endif // PLOTINGZ_PLOT_UTILITY_SRC_INPUT_DATA_UTILITY_H_
