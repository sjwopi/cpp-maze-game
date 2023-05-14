#define _USE_MATH_DEFINES
#include "Build.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include "allObjectsInTheGame.h"

bool Build::GAME(float& timeS, UserInfo& data) {
    srand(time(NULL));
    allObjectsInTheGame gameObject(*window, 2160, 1400, 8, 8, 10, 10, 3, 5);
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f pos = window->mapPixelToCoords(pixelPos);
    sf::Clock clock;
    sf::View view;
    view.setSize(500, 250);;
    float tempX = gameObject.getPlayer()->getPosition().x, tempY = gameObject.getPlayer()->getPosition().y;
    if (gameObject.getPlayer()->getPosition().x < 250)
        tempX = 250;
    if (gameObject.getPlayer()->getPosition().y < 125)
        tempY = 125;
    if (gameObject.getPlayer()->getPosition().y > 1275)
        tempY = 1275;
    if (gameObject.getPlayer()->getPosition().x > 1910)
        tempX = 1910;
    view.setCenter(tempX, tempY);
    sf::Texture portal;
    portal.loadFromFile("image/portal.png");

    sf::CircleShape shape1;
    shape1.setTexture(&portal);
    shape1.setRadius(20);
    shape1.setOrigin(20, 20);
    shape1.setPosition(gameObject.getMap()->getRandomCenterRooms());

    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;
    sf::Vector2f Player;

    while (window->isOpen())
    {
        timeS += clock.getElapsedTime().asSeconds();
        sf::Event event;
        double time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 2450;
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
        sf::Vector2f pos = window->mapPixelToCoords(pixelPos);
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                return false;

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                return false;
            }
        }
        window->clear();
        gameObject.getPlayer()->Rotation(pos);

        gameObject.getMap()->draw(*window);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            gameObject.getPlayer()->Play("Left", 0.5, time, gameObject.getMap()->GetWalls(), view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            gameObject.getPlayer()->Play("Right", 0.5, time, gameObject.getMap()->GetWalls(), view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            gameObject.getPlayer()->Play("Up", 0.5, time, gameObject.getMap()->GetWalls(), view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            gameObject.getPlayer()->Play("Down", 0.5, time, gameObject.getMap()->GetWalls(), view);
        }

        Player = sf::Vector2f(gameObject.getPlayer()->getPosition());
        aimDir = pos - Player;
        aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

        float Lx = sin(((gameObject.getPlayer()->getRotation()) * M_PI) / 180) * 17;
        float Ly = cos(((gameObject.getPlayer()->getRotation()) * M_PI) / 180) * 17;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            gameObject.getPlayer()->shoot(time, aimDirNorm, sf::Vector2f(Player.x - Lx - 0.01, Player.y + Ly + 0.01));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            gameObject.getPlayer()->reload();
        }
        for (auto& i : gameObject.getAllBonuses()) {
            if (!i->isTaken()) {
                i->draw(*window);
                if (gameObject.getPlayer()->intersects(i->getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                        i->apply(*(gameObject.getPlayer()));
                    }
                }
            }
        }
        gameObject.getWeaponBonus()->draw(*window);
        gameObject.getWeaponBonus()->update(time);
        if (gameObject.getPlayer()->intersects(gameObject.getWeaponBonus()->getGlobalBounds())) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                gameObject.getWeaponBonus()->apply(*(gameObject.getPlayer()));
                gameObject.getStatusbar()->setNameTextureWeaponIcon(gameObject.getPlayer()->getPathWeapon());
            }
        }
        for (auto& i : gameObject.getTurels()) {
            i->fire(Player, sf::Vector2f(i->getPosition().x, i->getPosition().y));
            i->update(time, *(gameObject.getPlayer()));
            i->draw(*window);
        }
        for (auto& i : gameObject.getGhostspawns()) {
            i->update(time, *(gameObject.getPlayer()));
            i->draw(*window);
            for (auto& j : i->getGhosts()) {
                gameObject.getGhosts().push_back(&j);
            }
        }
        gameObject.getPlayer()->updatePlayer(time, gameObject.getCharacters());
        gameObject.getPlayer()->updatePlayer(time, gameObject.getGhosts());
        gameObject.getPlayer()->renderShoot(*window);
        gameObject.getGhosts().clear();

        gameObject.getStatusbar()->update(*(gameObject.getPlayer()));
        gameObject.getStatusbar()->draw(*window);

        for (auto& mine : gameObject.getMines()) {
            mine->explosion(time, *(gameObject.getPlayer()));
            mine->draw(*window);
        }

        if (gameObject.getPlayer()->getHealth() <= 0) {
            data.countDeaths += 1;
            return false;
        }
        if (gameObject.getPlayer()->intersects(shape1.getGlobalBounds())) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                return true;
            }
        }
        window->draw(shape1);
        gameObject.getPlayer()->draw(*window);
        window->setView(view);
        window->display();
    }
};
void Build::level(float& timeS, UserInfo& data)
{
    if (GAME(timeS, data)) level(timeS, data);

}

UserInfo Build::game(std::string nick) {
    float timeS = 0.f;
    UserInfo data(nick, 0, 0, 0, " ");
    level(timeS, data);
    data.countGame += 1;
    data.time = std::to_string((int)timeS);
    this->menu();
    return data;

};

int Build::login() {
    bool flag = false;
    std::string nick = "user";

    while ((*window).isOpen())
    {
        sf::Event event;
        while ((*window).pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                (*window).close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                this->menu();
                return 1;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    int btnNumber = form.checkPressed(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
                    if (btnNumber == 1) {
                        nick = "";
                        flag = true;
                    }
                    if (btnNumber == 2) {
                        UserInfo data = this->game(nick);
                        statisticsView.setInfo(data.nick, data.countWin, data.countGame, data.countDeaths, data.time);
                        flag = 1;
                    }
                }
            }
            if (event.type == sf::Event::TextEntered && flag) {
                if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    if (nick.length() <= 15) {
                        nick += static_cast<char>(event.text.unicode);
                    }
                }
                if (event.text.unicode == '\b') {
                    if (nick.length() >= 1) {
                        nick.erase(nick.length() - 1, 1);
                    }
                }
            }
        }
        (*window).clear();
        form.drawLogin(nick);
        (*window).display();
    }
    return 0;
}

int Build::menu() {
    (*window).setView((*window).getDefaultView());
    (*window).clear();
    form.drawMenu();
    return 0;
}

int Build::statistics() {

    while ((*window).isOpen())
    {
        sf::Event event;
        while ((*window).pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                (*window).close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                form.drawMenu();
                return 1;
            }
        }
        (*window).clear();
        statisticsView.draw(*window);
        (*window).display();
    }
    return 0;
}