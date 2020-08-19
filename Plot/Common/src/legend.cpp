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

    std::vector<sf::RectangleShape> legend_shapes;
    legend_shapes.reserve(1 + labels_.size());
    legend_shapes.emplace_back(CreateLegendFrame());

    const auto label_boxes = CreateLabelBoxes();
    std::move(label_boxes.cbegin(), label_boxes.cend(), std::back_inserter(legend_shapes));

    plotting_data_->SetLegendShapes(legend_shapes);

    std::vector<sf::Text> label_texts = CreateLabelText();
    plotting_data_->SetLegendLabels(label_texts);
}

std::vector<sf::RectangleShape> Legend::CreateLabelBoxes() {
    std::vector<sf::RectangleShape> label_boxes;

    label_boxes.reserve(labels_.size());

    for (std::size_t i{0}; i < labels_.size(); i++) {
        sf::RectangleShape label_box;
        /// @todo: Set fill color based on input data shape color
        label_box.setSize({10.0f, 10.0f});
        label_box.setFillColor(mapped_colors.at(i));
        label_box.setPosition(Config::WINDOW_WIDTH * 0.65, Config::WINDOW_HEIGHT * 0.056);
        label_box.move(5.0f, Config::LABEL_POSITION_OFFSET.y * i);
        label_boxes.emplace_back(label_box);
    }
    return label_boxes;
}

std::vector<sf::Text> Legend::CreateLabelText() {
    Global::SetFont();
    std::vector<sf::Text> label_texts;
    for (std::size_t i{0}; i < labels_.size(); ++i) {
        sf::Text label_text;
        label_text.setFont(Config::FONT);
        label_text.setFillColor(sf::Color::Black);
        label_text.setCharacterSize(Config::LEGEND_FONT_SIZE);
        label_text.setString(labels_.at(i));
        label_text.setPosition(Config::WINDOW_WIDTH * 0.65, Config::WINDOW_HEIGHT * 0.05);
        label_text.move(Config::LABEL_POSITION_OFFSET.x, Config::LABEL_POSITION_OFFSET.y * i);
        label_texts.emplace_back(label_text);
    }
    return label_texts;
}

sf::RectangleShape Legend::CreateLegendFrame() {
    sf::RectangleShape legend_frame;
    legend_frame.setPosition(
            {Config::WINDOW_WIDTH * 0.65, Config::WINDOW_HEIGHT * 0.05});
    legend_frame.setSize({200.f, 18.f * labels_.size()});
    legend_frame.setFillColor(sf::Color::White);
    legend_frame.setOutlineThickness(Config::LEGEND_FRAME_LINE_THICKNESS);
    legend_frame.setOutlineColor(sf::Color::Black);
    return legend_frame;
}

const std::vector<std::string> &Legend::GetLabels() const {
    return labels_;
}
