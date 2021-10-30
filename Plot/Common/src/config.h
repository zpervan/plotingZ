#ifndef PLOTINGZ_CONFIG_H
#define PLOTINGZ_CONFIG_H

#ifdef __linux__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#endif

#include "ThirdParty/SFML/include/SFML/Graphics/RectangleShape.hpp"
#include "ThirdParty/SFML/include/SFML/Graphics/Text.hpp"
#include "ThirdParty/SFML/include/SFML/System/Vector2.hpp"
// #include <zconf.h>

using AxisData = std::pair<std::vector<sf::RectangleShape>, std::vector<sf::Text>>;

namespace Config
{

  static constexpr unsigned int WINDOW_WIDTH{640};
  static constexpr unsigned int WINDOW_HEIGHT{480};
  static constexpr unsigned int AXIS_FONT_SIZE{16};

  static constexpr float MARKER_LENGTH{10.0};
  static constexpr float AXIS_LINE_THICKNESS{2.0};
  static constexpr float EDGE_OFFSET{80.0};

  static const sf::Vector2f REFERENCE_POINT{WINDOW_WIDTH * 0.1, WINDOW_HEIGHT * 0.9};
  static const sf::Vector2f X_AXIS_MARKER_REFERENCE_POINT{REFERENCE_POINT.x - MARKER_LENGTH / 2,
                                                          REFERENCE_POINT.y + AXIS_FONT_SIZE / 2};
  static const sf::Vector2f Y_AXIS_MARKER_REFERENCE_POINT{REFERENCE_POINT.x - MARKER_LENGTH * 3,
                                                          REFERENCE_POINT.y - AXIS_FONT_SIZE / 2};

  static const sf::Vector2f MARKER_DIMENSION{MARKER_LENGTH, AXIS_LINE_THICKNESS};
  static const sf::Vector2f X_AXIS_DIMENSION{WINDOW_WIDTH - EDGE_OFFSET, AXIS_LINE_THICKNESS};
  static const sf::Vector2f Y_AXIS_DIMENSION{AXIS_LINE_THICKNESS, WINDOW_HEIGHT - EDGE_OFFSET};

  namespace Axis
  {
    static std::size_t MIN_NUMBER_OF_MARKERS{3};
    static std::size_t MAX_NUMBER_OF_MARKERS{10};
  } // namespace Axis

  namespace Legend
  {
    static constexpr float FONT_SIZE{12.0};
    static constexpr float FONT_PIXEL_SCALE{1.33};
    static constexpr float FRAME_LINE_THICKNESS{1.0};
    static constexpr float LABEL_BOX_OFFSET{1.0};

    static const sf::Vector2f LABEL_BOX_POSITION_OFFSET{5.0, 17.5};
    static const sf::Vector2f LABEL_BOX_SIZE{13.0, 13.0};
    static const sf::Vector2f LABEL_TEXT_POSITION_OFFSET{LABEL_BOX_POSITION_OFFSET.x * 4,
                                                         LABEL_BOX_POSITION_OFFSET.y};
    static const sf::Vector2f FRAME_POSITION_ORIGIN{Config::WINDOW_WIDTH * 0.70, Config::WINDOW_HEIGHT * 0.05};
    static const sf::Vector2f FRAME_SIZE{FONT_SIZE, 18};
  } // namespace Legend

  namespace ScatterPlot
  {
    static constexpr float DATA_POINT_RADIUS{2.0};
    static constexpr float DATA_POINT_X_OFFSET{DATA_POINT_RADIUS / 2};
    static constexpr float DATA_POINT_Y_OFFSET{DATA_POINT_RADIUS + 0.5};
  } // namespace ScatterPlot

  namespace Global
  {
    static sf::Font FONT{};

    /// @todo: Create a function which initializes the font object?
    static void SetFont()
    {
      sf::Font font;
      font.loadFromFile("Plot/Fonts/CodeNewRoman_NerdFont.otf");
      FONT = font;
    }
  } // namespace Global
} // namespace Config

#endif // PLOTINGZ_CONFIG_H
