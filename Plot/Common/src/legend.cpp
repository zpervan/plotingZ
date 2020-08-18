#include "Plot/Common/src/legend.h"

void Legend::SetLegendLabels(const std::vector<std::string> &labels) {
    labels_.reserve(labels.size());
    std::move(labels.cbegin(), labels.cend(), std::back_inserter(labels_));
}

void Legend::CreateLegend() {
    std::vector<sf::RectangleShape> legend_shapes;
    legend_shapes.emplace_back(CreateLegendFrame());

    plotting_data_->SetLegendShapes(legend_shapes);
}

std::vector<sf::RectangleShape> Legend::CreateLabelBoxes() {
    std::vector<sf::RectangleShape> label_boxes;

    label_boxes.reserve(labels_.size());

    for (std::size_t i{0}; i < labels_.size(); i++) {
        sf::RectangleShape label_box;
//        label_box.setPosition(
//                {);
//        label_box.
    }
    return std::vector<sf::RectangleShape>();
}

std::vector<sf::Font> Legend::CreateLabelText() {
    return std::vector<sf::Font>();
}

sf::RectangleShape Legend::CreateLegendFrame() {
    sf::RectangleShape legend_frame;
    legend_frame.setPosition(
            {Config::WINDOW_WIDTH * 0.65, Config::WINDOW_HEIGHT * 0.05});
    legend_frame.setSize({200.f, 25.f});
    legend_frame.setFillColor(sf::Color::White);
    legend_frame.setOutlineThickness(Config::LINE_THICKNESS);
    legend_frame.setOutlineColor(sf::Color::Black);
    return legend_frame;
}
