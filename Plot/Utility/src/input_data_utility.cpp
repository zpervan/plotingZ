#include "Plot/Utility/src/input_data_utility.h"

#include <cmath>

SineData InputData::GenerateSineWave(const WaveformParameters &parameters) {
  std::vector<float> value;
  std::vector<float> time;
  float sample_rate_value{0.0};

  for (std::size_t current_time{0}; current_time <= parameters.duration; current_time++) {
    sample_rate_value += parameters.sample_rate;
    auto angular_frequency = 2.0f * M_PI * sample_rate_value;
    auto calculated_value = parameters.amplitude * std::sin(angular_frequency + parameters.phase_shift) + parameters.vertical_shift;

    value.emplace_back(calculated_value);
    time.emplace_back(current_time);
  }

  return {time, value};
}