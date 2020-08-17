#include "Plot/Main/src/main.h"
#include "Plot/Common/src/config.h"
#include <SFML/Graphics.hpp>


void PlottingZ::SetData(const std::vector<float> &input_data_x, const std::vector<float> &input_data_y) {
    if (input_data_x.empty() || input_data_y.empty()) {
        throw std::invalid_argument("Given input data is empty! Check passed data.");
    }

    if (input_data_x.size() != input_data_y.size()) {
        throw std::invalid_argument("Size of given input data does not match and should be of the same size!");
    }

    plotting_data_.SetMaxXValue(input_data_x);
    plotting_data_.SetMaxYValue(input_data_y);
    plotting_data_.AppendToInputDataValuesCollection(input_data_x, input_data_y);
}

void PlottingZ::Plot() {


    sf::RenderWindow window{{Config::WINDOW_HEIGHT, Config::WINDOW_WIDTH}, "wot"};
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        // Add drawing logic
        window.display();
    }

}

void PlottingZ::SetAxis() {}

void PlottingZ::SetPlotType(PlotType plot_type) {
    plot_type_ = plot_type;
}

const PlottingData &PlottingZ::GetPlottingData() const {
    return plotting_data_;
}
