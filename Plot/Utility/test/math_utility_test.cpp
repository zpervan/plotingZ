#include "Plot/Utility/src/math_utility.h"
#include "ThirdParty/fmt/include/fmt/core.h"

#include "gtest/gtest.h"

static inline std::string PrintValues(const sf::Vector2f &first_point, const sf::Vector2f &second_point) {
  return fmt::format("First point: {}, {}\nSecond point: {}, {}\n", first_point.x, first_point.y,
                     second_point.x, second_point.y);
}

class MathUtilityAngleCalculationTestFixture
    : public testing::TestWithParam<std::tuple<sf::Vector2f, sf::Vector2f, float>> {};

TEST_P(MathUtilityAngleCalculationTestFixture,
       GivenTwo2dPoints_WhenCalculatingAngleBetweenTwoPoints_ThenCorrectAngleCalculated) {
  const auto &[first_point, second_point, expected_angle] = GetParam();
  const double actual_calculated_angle =
      MathUtility::CalculateAngleBetweenTwo2DPoints(first_point, second_point);

  EXPECT_FLOAT_EQ(actual_calculated_angle, expected_angle) << PrintValues(first_point, second_point);
}

INSTANTIATE_TEST_SUITE_P(
    CalculateAngleParametrizedTest, MathUtilityAngleCalculationTestFixture,
    testing::Values(std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {1.0, 1.0}, 45.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {0.0, 1.0}, 90.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {-1.0, 1.0}, 135.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {-1.0, 0.0}, 180.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {-1.0, -1.0}, 225.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {0.0, -1.0}, 270.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {1.0, -1.0}, 315.0)));

class MathUtilityDistanceCalculationTestFixture
    : public testing::TestWithParam<std::tuple<sf::Vector2f, sf::Vector2f, float>> {};

TEST_P(MathUtilityDistanceCalculationTestFixture,
       GivenTwo2dPoints_WhenCalculatingDistanceBetweenTwoPoints_ThenCorrectDistanceCalculated) {
  const auto &[first_point, second_point, expected_distance] = GetParam();
  const double actual_calculated_distance =
      MathUtility::CalculateDistanceBetweenTwo2DPoints(first_point, second_point);

  EXPECT_FLOAT_EQ(actual_calculated_distance, expected_distance) << PrintValues(first_point, second_point);
}

INSTANTIATE_TEST_SUITE_P(
    CalculateDistanceParametrizedTest, MathUtilityDistanceCalculationTestFixture,
    testing::Values(std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {0.0, 0.0}, 0.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {1.0, 1.0}, 1.4142135),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {-1.0, 1.0}, 1.4142135),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {-1.0, 0.0}, 1.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {-1.0, -1.0}, 1.4142135),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {0.0, -1.0}, 1.0),
                    std::make_tuple<sf::Vector2f, sf::Vector2f, float>({0.0, 0.0}, {1.0, -1.0}, 1.4142135)));

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
