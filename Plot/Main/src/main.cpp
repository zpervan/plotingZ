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

    plotting_data_->FindAndSetMaxXValue(input_data_x);
    plotting_data_->FindAndSetMaxYValue(input_data_y);
    plotting_data_->AppendToInputDataValuesCollection(input_data_x, input_data_y);

    SetAxis();
}

void PlottingZ::Plot() {

    axis_.CreateAxis();

    sf::RenderWindow window{{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}, "wot"};

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);

        for (const auto &axis_shape : plotting_data_->GetAxisShapes()) {
            window.draw(axis_shape);
        }

        for (const auto &axis_marker_values : plotting_data_->GetAxisMarkerValues()) {
            window.draw(axis_marker_values);
        }

        window.display();
    }

}

void PlottingZ::SetAxis() {
    axis_.SetXAxis(plotting_data_->GetMaxXValue());
    axis_.SetYAxis(plotting_data_->GetMaxYValue());
}

void PlottingZ::SetPlotType(PlotType plot_type) {
    plot_type_ = plot_type;
}

const PlottingData &PlottingZ::GetPlottingData() const {
    return *plotting_data_;
}
