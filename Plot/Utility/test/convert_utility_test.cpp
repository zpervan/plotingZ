#include "Plot/Utility/src/convert_utility.h"
#include "ThirdParty/fmt/include/fmt/core.h"

#include "gtest/gtest.h"

class NormalizeValueDeathTestFixture : public ::testing::TestWithParam<std::tuple<float, float>> {};

TEST_P(NormalizeValueDeathTestFixture, GivenNegativeValues_WhenNormalizingValue_ThenAssertIsThrown) {
  const auto &[value, scaling_value] = GetParam();

  EXPECT_DEATH(ConvertUtility::NormalizeValue(value, scaling_value), "");
}

INSTANTIATE_TEST_SUITE_P(NormalizeValueParametrizedDeathTest, NormalizeValueDeathTestFixture,
                         testing::Values(std::make_tuple<float, float>(-0.0001, 0.0),
                                         std::make_tuple<float, float>(0.0, -0.0001),
                                         std::make_tuple<float, float>(-0.01, -0.0001)));

class NormalizeValueTestFixture : public testing::TestWithParam<std::tuple<float, float, float>> {};

TEST_P(NormalizeValueTestFixture, GivenPositiveValue_WhenNormalazingValue_ThenNormalizedValueIsCorrect) {
  const auto &[value, scaling_value, expected_normalized_value] = GetParam();

  const float actual_normalized_value = ConvertUtility::NormalizeValue(value, scaling_value);

  EXPECT_FLOAT_EQ(expected_normalized_value, actual_normalized_value);
}

INSTANTIATE_TEST_SUITE_P(NormalizeValueParametrizedTest, NormalizeValueTestFixture,
                         testing::Values(std::make_tuple<float, float, float>(0.0, 0.0, 0.0),
                                         std::make_tuple<float, float, float>(1.0, 1.0, 1.0),
                                         std::make_tuple<float, float, float>(50.0, 100.0, 0.5)));

class ConvertNormalizedPointToAxisScreenSpaceDeathTestFixture
    : public ::testing::TestWithParam<sf::Vector2f> {};

TEST_P(ConvertNormalizedPointToAxisScreenSpaceDeathTestFixture,
       GivenInvalid2DNormalizedValues_WhenConverting_ThenAssertIsThrown) {
  const auto &normalized_value = GetParam();

  EXPECT_DEATH(ConvertUtility::ConvertNormalizedPointToAxisScreenSpace(normalized_value), "");
}

INSTANTIATE_TEST_SUITE_P(ConvertNormalizedPointToAxisScreenSpaceParametrizedDeathTest,
                         ConvertNormalizedPointToAxisScreenSpaceDeathTestFixture,
                         testing::Values(sf::Vector2{-0.0001, 0.0001}, sf::Vector2{0.0001, -0.0001},
                                         sf::Vector2{-0.0001, -0.0001}, sf::Vector2{1.0001, 1.0},
                                         sf::Vector2{1.0, 1.0001}, sf::Vector2{1.0001, 1.0001}));

class ConvertNormalizedPointToAxisScreenSpaceTestFixture
    : public testing::TestWithParam<std::tuple<sf::Vector2f, sf::Vector2f>> {};

TEST_P(ConvertNormalizedPointToAxisScreenSpaceTestFixture,
       GivenValidNormalized2DPoints_WhenConverting_ThenAxisScreenSpaceValueIsCorrect) {
  const auto &[normalized_point, expected_converted_value] = GetParam();

  const sf::Vector2f actual_converted_value =
      ConvertUtility::ConvertNormalizedPointToAxisScreenSpace(normalized_point);

  EXPECT_EQ(expected_converted_value.x, actual_converted_value.x);
  EXPECT_EQ(expected_converted_value.y, actual_converted_value.y);
}

INSTANTIATE_TEST_SUITE_P(
    ConvertNormalizedPointToAxisScreenSpaceParametrizedTest,
    ConvertNormalizedPointToAxisScreenSpaceTestFixture,
    testing::Values(std::make_tuple<sf::Vector2f, sf::Vector2f>({0.0, 0.0}, {0.0, 0.0}),
                    std::make_tuple<sf::Vector2f, sf::Vector2f>({0.25, 0.25}, {140.0, 100.0}),
                    std::make_tuple<sf::Vector2f, sf::Vector2f>({0.5, 0.5}, {280.0, 200.0}),
                    std::make_tuple<sf::Vector2f, sf::Vector2f>({0.75, 0.75}, {420.0, 300.0}),
                    std::make_tuple<sf::Vector2f, sf::Vector2f>({1.0, 1.0}, {560.0, 400.0})));

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
