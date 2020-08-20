#include "Plot/Common/src/legend.h"
#include "Plot/Common/src/types.h"

void Legend::SetLegendLabels(const std::vector<std::string> &labels) {
    labels_.reserve(labels.size());
    std::move(labels.cbegin(), labels.cend(), std::back_inserter(labels_));
}

void Legend::CreateLegend() {
    if (labels_.empty()) {
        throw std::invalid_argument("Legend labels are not set!");
    }

    sf::RectangleShape legend_frame = CreateLegendFrame();
    std::vector<sf::RectangleShape> label_boxes = CreateLabelBoxes();

    std::vector<sf::RectangleShape> legend_shapes;
    legend_shapes.reserve(1 + labels_.size());
    legend_shapes.emplace_back(legend_frame);
    std::move(label_boxes.cbegin(), label_boxes.cend(), std::back_inserter(legend_shapes));

    plotting_data_->SetLegendShapes(legend_shapes);

    std::vector<sf::Text> label_texts = CreateLabelText();
    plotting_data_->SetLegendLabels(label_texts);
}

/// @todo: Scale X-axis with the label text (frame size should be large as the largest label text)
sf::RectangleShape Legend::CreateLegendFrame() {
    sf::RectangleShape legend_frame;
    legend_frame.setPosition(Config::Legend::FRAME_POSITION_ORIGIN);
    legend_frame.setSize({Config::Legend::FRAME_SIZE.x, Config::Legend::FRAME_SIZE.y * labels_.size()});
    legend_frame.setOutlineThickness(Config::Legend::FRAME_LINE_THICKNESS);
    legend_frame.setFillColor(sf::Color::White);
    legend_frame.setOutlineColor(sf::Color::Black);

    return legend_frame;
}

static inline sf::Vector2f CalculateLabelBoxOriginPosition() {
    return {Config::Legend::FRAME_POSITION_ORIGIN.x,
            Config::Legend::FRAME_POSITION_ORIGIN.y * Config::Legend::LABEL_BOX_OFFSET};
}

/// @todo: Set fill color based on input data shape color
std::vector<sf::RectangleShape> Legend::CreateLabelBoxes() {
    std::vector<sf::RectangleShape> label_boxes;
    label_boxes.reserve(labels_.size());

    for (std::size_t i{0}; i < labels_.size(); i++) {
        sf::RectangleShape label_box;
        label_box.setSize(Config::Legend::LABEL_BOX_SIZE);
        label_box.setFillColor(mapped_colors.at(i));
        label_box.setPosition(CalculateLabelBoxOriginPosition());
        label_box.move(Config::Legend::LABEL_BOX_POSITION_OFFSET.x, Config::Legend::LABEL_BOX_POSITION_OFFSET.y * i);
        label_boxes.emplace_back(label_box);
    }
    return label_boxes;
}

std::vector<sf::Text> Legend::CreateLabelText() {
    Config::Global::SetFont();
    std::vector<sf::Text> label_texts;
    for (std::size_t i{0}; i < labels_.size(); i++) {
        sf::Text label_text;
        label_text.setFont(Config::Global::FONT);
        label_text.setFillColor(sf::Color::Black);
        label_text.setCharacterSize(Config::Legend::FONT_SIZE);
        label_text.setString(labels_.at(i));
        label_text.setPosition(Config::Legend::FRAME_POSITION_ORIGIN);
        label_text.move(Config::Legend::LABEL_TEXT_POSITION_OFFSET.x,
                        Config::Legend::LABEL_TEXT_POSITION_OFFSET.y * i);

        label_texts.emplace_back(label_text);
    }
    return label_texts;
}

const std::vector<std::string> &Legend::GetLabels() const {
    return labels_;
}
