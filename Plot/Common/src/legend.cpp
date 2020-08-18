#include "Plot/Common/src/legend.h"

void Legend::SetLegendLabels(const std::vector<std::string> &labels) {
    labels_.reserve(labels.size());
    std::move(labels.cbegin(), labels.cend(), std::back_inserter(labels_));
}

void Legend::CreateLegend() {

}

std::vector<sf::RectangleShape> Legend::CreateLabelBoxes() {
    std::vector<sf::RectangleShape> label_boxes;
    label_boxes.reserve(labels_.size());
    for (std::size_t i{0}; i < labels_.size(); i++) {
        sf::RectangleShape label_box;
        label_box.setPosition(Config::REFERENCE_POINT);
//        label_box.
    }
    return std::vector<sf::RectangleShape>();
}

std::vector<sf::Font> Legend::CreateLabelText() {
    return std::vector<sf::Font>();
}

sf::RectangleShape Legend::CreateLegendFrame() {
    sf::RectangleShape legend_frame;
    legend_frame.setPosition(Config::REFERENCE_POINT);
    legend_frame.setSize({50, 50});
    legend_frame.setFillColor(sf::Color::White);
    legend_frame.setOutlineColor(sf::Color::Black);
    return legend_frame;
}
