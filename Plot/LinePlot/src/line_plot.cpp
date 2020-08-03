#include "line_plot.h"

#include "ThirdParty/fmt/include/fmt/core.h"
#include <SFML/Graphics.hpp>
#include "Plot/Common/src/config.h"

void LinePlot::Plot(const std::string &title) {
    fmt::print("Called plot function...");

    sf::RenderWindow window{{Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}, title};
    axis_.SetYAxis(5);
    axis_.SetXAxis(2);
    axis_.DrawAxis();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);

        for (const auto &shape : axis_.GetAxisShapes()) {
            window.draw(shape);
        }

        for (const auto &marker_value : axis_.GetAxisMarkerValues()) {
            window.draw(marker_value);
        }
        window.display();
    }
}

void LinePlot::SetData(const std::vector<int> &data) {
    std::move(data.cbegin(), data.cend(), data_.begin());
}
