#include "Plot/Utility/src/input_data_utility.h"

#include "gtest/gtest.h"

TEST(InputDataUtilityTest, GivenPredefinesSampleRate_WhenGeneratingSineData_ThenCorrectValuesGenerated)
{
  constexpr float sample_rate = 1;
  auto& actual_sine_dataInputData::GenerateSineWave();
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}