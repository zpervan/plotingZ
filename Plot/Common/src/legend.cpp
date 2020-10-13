#include "Plot/Common/src/legend.h"
#include "Plot/Common/src/config.h"
#include "Plot/Common/src/types.h"

#include <cassert>

void Legend::SetLegendLabels(const std::vector<std::string> &labels) {
  labels_.reserve(labels.size());
  std::move(labels.cbegin(), labels.cend(), std::back_inserter(labels_));
}

void Legend::CreateLegend() {
  if (labels_.empty()) {
	throw std::invalid_argument("Legend labels are not set!");
  }

  sf::RectangleShape legend_frame{CreateLegendFrame()};
  std::vector<sf::RectangleShape> label_colour_boxes{CreateLabelColourBoxes()};

  std::vector<sf::RectangleShape> legend_shapes;
  legend_shapes.reserve(1 + labels_.size());
  legend_shapes.emplace_back(std::move(legend_frame));

  std::move(label_colour_boxes.cbegin(), label_colour_boxes.cend(), std::back_inserter(legend_shapes));
  plotting_data_->SetLegendShapes(legend_shapes);

  std::vector<sf::Text> label_texts{CreateLabelText()};
  plotting_data_->SetLegendLabels(label_texts);
}

sf::RectangleShape Legend::CreateLegendFrame() {
  CalculateLegendFrameDimension();
  CalculateLegendFramePosition();

  sf::RectangleShape legend_frame;
  legend_frame.setSize(legend_frame_dimension_);
  legend_frame.setPosition(legend_frame_position_);
  legend_frame.setOutlineThickness(Config::Legend::FRAME_LINE_THICKNESS);
  legend_frame.setFillColor(sf::Color::White);
  legend_frame.setOutlineColor(sf::Color::Black);

  return legend_frame;
}

/// @todo: Set fill color based on input data shape color
std::vector<sf::RectangleShape> Legend::CreateLabelColourBoxes() {
  std::vector<sf::RectangleShape> label_colour_boxes;
  label_colour_boxes.reserve(labels_.size());

  // Needs to be calculated just once!
  const float x_position{CalculateLabelColourBoxXPosition()};

  for (std::size_t i{0}; i < labels_.size(); i++) {
	sf::RectangleShape label_colour_box;
	label_colour_box.setSize(Config::Legend::LABEL_BOX_SIZE);
	label_colour_box.setFillColor(mapped_colors.at(i));

	const float y_position{CalculateLabelColourBoxYPosition(i)};
	label_colour_box.setPosition(x_position, y_position);

	label_colour_boxes.emplace_back(std::move(label_colour_box));
  }
  return label_colour_boxes;
}

std::vector<sf::Text> Legend::CreateLabelText() {
  Config::Global::SetFont();

  // Needs to be calculated just once!
  const float x_position{CalculateLabelTextXPosition()};

  std::vector<sf::Text> label_texts;
  for (std::size_t i{0}; i < labels_.size(); i++) {
	sf::Text label_text;
	label_text.setFont(Config::Global::FONT);
	label_text.setFillColor(sf::Color::Black);
	label_text.setCharacterSize(Config::Legend::FONT_SIZE);
	label_text.setString(labels_.at(i));

	const float y_position{CalculateLabelTextYPosition(i)};
	label_text.setPosition(x_position, y_position);

	label_texts.emplace_back(label_text);
  }
  return label_texts;
}

float Legend::CalculateLabelColourBoxXPosition() {
  return legend_frame_position_.x + Config::Legend::LABEL_BOX_OFFSET;
}

float Legend::CalculateLabelColourBoxYPosition(const std::size_t position_offset) {
  const float offset_from_frame{((legend_frame_dimension_.y / labels_.size()) - Config::Legend::LABEL_BOX_SIZE.y) / 2};
  const float colour_box_y_offset{(legend_frame_dimension_.y / labels_.size()) * position_offset + offset_from_frame};
  return legend_frame_position_.y + colour_box_y_offset;
}

const std::vector<std::string> &Legend::GetLabels() const {
  return labels_;
}

void Legend::CalculateLegendFrameDimension() {
  const auto max_label_size =
	  std::max_element(labels_.cbegin(), labels_.cend(), [](const std::string &lhs, const std::string &rhs) {
		return lhs.length() < rhs.length();
	  })->size();

  const float x_dimension{Config::Legend::FRAME_SIZE.x * (max_label_size / Config::Legend::FONT_PIXEL_SCALE)};
  const float y_dimension{Config::Legend::FRAME_SIZE.y * labels_.size()};
  legend_frame_dimension_ = {x_dimension, y_dimension};
}

void Legend::CalculateLegendFramePosition() {
  assert(IsLegendFrameDimensionCalculated() && "Legend frame position is not calculated!");

  constexpr float position_offset{10.0};
  const float legend_frame_x_position{Config::WINDOW_WIDTH - legend_frame_dimension_.x - position_offset};
  const float legend_frame_y_position{Config::Legend::FRAME_POSITION_ORIGIN.y - position_offset};

  legend_frame_position_ = {legend_frame_x_position, legend_frame_y_position};
}

bool Legend::IsLegendFrameDimensionCalculated() const {
  return (legend_frame_dimension_.x > 0.0) && (legend_frame_dimension_.y > 0.0);
}

float Legend::CalculateLabelTextXPosition() {
  return CalculateLabelColourBoxXPosition() + Config::Legend::LABEL_BOX_SIZE.x;
}

float Legend::CalculateLabelTextYPosition(std::size_t position_offset) {
  const float text_y_offset{(legend_frame_dimension_.y / labels_.size()) * position_offset};
  return legend_frame_position_.y + text_y_offset;
}
