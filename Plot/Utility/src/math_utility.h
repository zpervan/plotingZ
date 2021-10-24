#ifndef PLOTINGZ_MATH_UTILITY_H
#define PLOTINGZ_MATH_UTILITY_H

#include "ThirdParty/SFML/include/SFML/System/Vector2.hpp"

namespace MathUtility {
/// @brief Calculates the angle of two 2D points in degrees
/// @param [in] first_point 2D point
/// @param [in] second_point 2D point
/// @return Angle in degrees between two points in the 2D world space (points)
float CalculateAngleBetweenTwo2DPoints(const sf::Vector2f &first_point, const sf::Vector2f &second_point);

/// @brief Calculates the distance between two 2D points
/// @param [in] first_point 2D point
/// @param [in] second_point 2D point
/// @return Distance between two points in the 2D world space (points)
float CalculateDistanceBetweenTwo2DPoints(const sf::Vector2f &first_point, const sf::Vector2f &second_point);
} // namespace MathUtility

#endif // PLOTINGZ_MATH_UTILITY_H
