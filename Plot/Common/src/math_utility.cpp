#include "Plot/Common/src/math_utility.h"

#include <cmath>

static inline std::pair<float, float>
CalculateDeltas(const sf::Vector2f &first_point, const sf::Vector2f &second_point);

float MathUtility::CalculateAngleBetweenTwo2DPoints(const sf::Vector2f &first_point, const sf::Vector2f &second_point) {
    const auto&[delta_x, delta_y] = CalculateDeltas(first_point, second_point);
    const float angle_degree = (atan2f(delta_y, delta_x) * 180.0f) / static_cast<float>(M_PI);
    return angle_degree < 0 ? 360.0f - std::abs(angle_degree) : angle_degree;
}

float
MathUtility::CalculateDistanceBetweenTwo2DPoints(const sf::Vector2f &first_point, const sf::Vector2f &second_point) {
    const auto&[delta_x, delta_y] = CalculateDeltas(first_point, second_point);
    const float squared_delta_x = std::pow(delta_x, 2);
    const float squared_delta_y = std::pow(delta_y, 2);
    return std::sqrt(squared_delta_x + squared_delta_y);
}

inline std::pair<float, float>
CalculateDeltas(const sf::Vector2f &first_point, const sf::Vector2f &second_point) {
    const float delta_x = second_point.x - first_point.x;
    const float delta_y = second_point.y - first_point.y;
    return {delta_x, delta_y};
}
