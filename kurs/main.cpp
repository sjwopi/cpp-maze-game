#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Statistics.h"
#include "Login.h"
#include "Build.h"


int main() {
    bool flag = true;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game");
    Menu menu(window.getSize().x, window.getSize().y);
    Login login(window.getSize().x, window.getSize().y);
    Statistics statistics;

    Build build(window);

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
                    int btnNumber = menu.checkPressed(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    if (btnNumber == 1) {
                        flag = 1;
                        build.login(window, menu, login, statistics);
                    }
                    else if (btnNumber == 2) {
                        flag = 1;
                        build.statistics(window, menu, login, statistics);
                    }
                }
            }
        }

        window.clear();

        if (flag) {
            build.menu(menu, login, statistics);
        }

        window.display();

    }
    return 0;
}