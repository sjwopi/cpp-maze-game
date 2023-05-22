#include <SFML/Graphics.hpp>
#include "Form.h"
#include "Statistics.h"
#include "Build.h"


int main() {
    bool flag = true;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game");
    Form form(window.getSize().x, window.getSize().y, window);
    Statistics statistics;
    Build build(form, statistics, window);

    while (window.isOpen())
    {
        sf::String nick = "username";

        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i position = sf::Mouse::getPosition();

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
                    int btnNumber = form.checkPressed(pos.x, pos.y);
                    if (btnNumber == 1) {
                        flag = 1;
                        build.login();
                    }
                    else if (btnNumber == 2) {
                        flag = 1;
                        build.statistics();
                    }
                    else if (btnNumber == 3) {
                        flag = 1;
                        build.settings();
                    }
                }
            }
        }

        window.clear();

        if (flag) {
            build.menu();
        }

        window.display();

    }
    return 0;
}