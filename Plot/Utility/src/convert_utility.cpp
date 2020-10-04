#include "Plot/Utility/src/convert_utility.h"
#include "Plot/Common/src/config.h"

#include <cassert>

sf::Vector2f ConvertUtility::NormalizeValues(const sf::Vector2f &data_point,
											 float scaling_value_x,
											 float scaling_value_y) {
  const float normalized_point_x = ConvertUtility::NormalizeValue(data_point.x, scaling_value_x);
  const float normalized_point_y = ConvertUtility::NormalizeValue(data_point.y, scaling_value_y);

  return {normalized_point_x, normalized_point_y};
}

float ConvertUtility::NormalizeValue(float value_to_normalize, float scaling_value) {
  assert((value_to_normalize >= 0.0) && (scaling_value >= 0.0));

  if ((value_to_normalize > 0.0) && (scaling_value > 0.0)) {
	return value_to_normalize / scaling_value;
  }
  return 0.0;
}

static inline void IsNormalizedValueInsideAllowedRange(const sf::Vector2f &normalized_point) {
  assert((normalized_point.x >= 0.0) && (normalized_point.x <= 1.0));
  assert((normalized_point.y >= 0.0) && (normalized_point.y <= 1.0));
}

sf::Vector2f ConvertUtility::ConvertNormalizedPointToAxisScreenSpace(const sf::Vector2f &normalized_point) {
  IsNormalizedValueInsideAllowedRange(normalized_point);

  const float converted_x_value = Config::X_AXIS_DIMENSION.x * normalized_point.x;
  const float converted_y_value = Config::Y_AXIS_DIMENSION.y * normalized_point.y;
  return {converted_x_value, converted_y_value};
}
