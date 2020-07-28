#include "line_plot.h"

#include "ThirdParty/fmt/include/fmt/core.h"
#include "ThirdParty/SFML/include/SFML/Graphics.hpp"
#include "Plot/Common/src/config.h"

void LinePlot::Plot(const std::string &title) {
    fmt::print("Called plot function...");

    sf::RenderWindow window{{Config::WindowWidth, Config::WindowHeight}, title};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);

        for (const auto shape : axis_.DrawAxis()) {
            window.draw(shape);
        }

        window.display();
    }
}

void LinePlot::SetData(const std::vector<int> &data) {
    std::move(data.cbegin(), data.cend(), data_.begin());
}
