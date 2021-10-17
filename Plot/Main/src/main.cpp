#include "Plot/Main/src/main.h"
#include "Plot/Common/src/config.h"

#include "include/SFML/Graphics.hpp"

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
}

void PlottingZ::Plot() {
  if (plot_type_ == PlotType::Unknown) {
    throw std::invalid_argument("Plot type not set!");
  }

  axis_.CreateAxis();
  InitializePlot();

  if (show_legend) {
    legend_.CreateLegend();
  }

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

    for (const auto &data_points : plotting_data_->GetPointDataCollection()) {
      for (const auto &data_point : data_points) {
        window.draw(data_point);
      }
    }

    for (const auto &data_lines : plotting_data_->GetLineDataValueCollection()) {
      for (const auto &data_line : data_lines) {
        window.draw(data_line);
      }
    }

    for (const auto &legend_shape : plotting_data_->GetLegendShapes()) {
      window.draw(legend_shape);
    }

    for (const auto &legend_labels : plotting_data_->GetLegendLabelTexts()) {
      window.draw(legend_labels);
    }

    window.display();
  }
}

/// @todo: Pass string instead of PlotType so that the user does not need to know about the PlotType data
/// type!
void PlottingZ::SetPlotType(PlotType plot_type) { plot_type_ = plot_type; }

void PlottingZ::InitializePlot() {
  if (plot_type_ == PlotType::ScatterPlot) {
    scatter_plot_ = ScatterPlot(plotting_data_.get());
    scatter_plot_.CreateScatterPlot();
  }

  if (plot_type_ == PlotType::LinePlot) {
    line_plot_ = LinePlot(plotting_data_.get());
    line_plot_.CreateLinePlot();
  }
}

void PlottingZ::SetLegendLabels(const std::vector<std::string> &labels) {
  show_legend = true;
  legend_.SetLegendLabels(labels);
}

const PlottingData &PlottingZ::GetPlottingData() const { return *plotting_data_; }
