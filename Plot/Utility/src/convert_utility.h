#ifndef PLOTINGZ_CONVERT_UTILITY_H
#define PLOTINGZ_CONVERT_UTILITY_H

#include "include/SFML/System/Vector2.hpp"
#include <utility>

using ScalingValues = std::pair<float, float>;

namespace ConvertUtility {
/// @brief Wrapper function which calls @function NormalizedValue and returns normalized values.
/// @attention Currently, does not support normalization with negative values!
/// @param [in] data_point Values which should be normalized
/// @param [in] scaling_value_x Scale (normalize) value to normalize the X input value
/// @param [in] scaling_value_y Scale (normalize) value to normalize the Y input value
/// @return Normalized values
sf::Vector2f NormalizeValues(const sf::Vector2f &data_point, float scaling_value_x, float scaling_value_y);

/// @brief Normalizes the value with given scaling value. The scaling value can (in most cases) be the max
/// value of a data set.
/// @attention Currently, does not support normalization with negative values!
/// @param [in] value_to_normalize Value which should be normalized
/// @param [in] scaling_value Scale (normalize) value to normalize the input value
/// @return Normalized value (between 0 and 1)
float NormalizeValue(float value_to_normalize, float scaling_value);

/// @brief Converts normalized point values to axis screen space values (represented in pixels). The axis
/// screen space represents the space between the horizontal (x) and vertical (y) axis.
/// @verbatim
///    ᴧ
/// +y |
///    |    axis
///    |     screen
///    |      space
///   -|-----------------> +x
/// @endverbatim
/// @param [in] normalized_point Normalized X and Y points
/// @return Axis screen space X and Y point in pixels
sf::Vector2f ConvertNormalizedPointToAxisScreenSpace(const sf::Vector2f &normalized_point);
} // namespace ConvertUtility

#endif // PLOTINGZ_CONVERT_UTILITY_H
