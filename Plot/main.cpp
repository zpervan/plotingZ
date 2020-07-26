#include "include/fmt/core.h"
#include "include/SFML/Graphics.hpp"

int main() {
    fmt::print("Hellllouuuu!");

    sf::RenderWindow window{{640,480}, "The title!"};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        window.display();
    }

    return 0;
}
