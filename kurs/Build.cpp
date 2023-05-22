#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>
#include "allObjectsInTheGame.h"
#include "Build.h"

bool Build::game(float& timeS, UserInfo& data, Player& hero) {
    srand(time(NULL));
    window->setFramerateLimit(30);
    ++lv;
    allObjectsInTheGame gameObject;
    gameObject.ñreate(*window, 2160, 1440, (5 * difficulty) + lv, (5 * difficulty) + lv, (5 * difficulty) + lv, (6 * difficulty) + lv, (4 * difficulty) + lv, (4 * difficulty) + lv);
    std::vector<GameObject> Walls = gameObject.getMap()->getWalls();
    gameObject.getStatusbar()->setLevel(lv);
    hero.setPosition(gameObject.getMap()->getRandomCenterRooms());
    hero.setWeapon(gameObject.getGun());
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f pos = window->mapPixelToCoords(pixelPos);
    sf::Clock clock;
    sf::View view;
    view.setSize(500, 250);
    float tempX = hero.getPosition().x, tempY = hero.getPosition().y;
    if (hero.getPosition().x < 250)
        tempX = 250;
    if (hero.getPosition().y < 125)
        tempY = 125;
    if (hero.getPosition().y > 1275)
        tempY = 1275;
    if (hero.getPosition().x > 1910)
        tempX = 1910;
    view.setCenter(tempX, tempY);
    if (lv == 6) {
        return false;
    }
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;
    sf::Vector2f Player;
    gameObject.getPortal()->setPosition(gameObject.getMap()->getRandomCenterRooms());

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
        hero.Rotation(pos);

        gameObject.getMap()->draw(*window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            hero.play("Left", 0.5, time, Walls, view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            hero.play("Right", 0.5, time, Walls, view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            hero.play("Up", 0.5, time, Walls, view);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            hero.play("Down", 0.5, time, Walls, view);
        }

        Player = sf::Vector2f(hero.getPosition());
        aimDir = pos - Player;
        aimDirNorm = aimDir / (float)sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

        float Lx = sin(((hero.getRotation()) * M_PI) / 180) * 17;
        float Ly = cos(((hero.getRotation()) * M_PI) / 180) * 17;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            hero.shoot(time, aimDirNorm, sf::Vector2f(Player.x - Lx - 0.01, Player.y + Ly + 0.01));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            hero.reload();
        }
        for (auto& i : gameObject.getAllBonuses()) {
            if (!i->isTaken()) {
                i->draw(*window);
                if (hero.intersects(i->getGlobalBounds())) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                        i->apply(hero);
                    }
                }
            }
        }
        gameObject.getWeaponBonus()->draw(*window);
        gameObject.getWeaponBonus()->update(time);
        if (hero.intersects(gameObject.getWeaponBonus()->getGlobalBounds())) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                gameObject.getWeaponBonus()->apply(hero);
                gameObject.getStatusbar()->setNameTextureWeaponIcon(hero.getPathWeapon());
            }
        }
        for (auto& i : gameObject.getTurels()) {
            i->fire(Player, sf::Vector2f(i->getPosition().x, i->getPosition().y));
            i->update(time, hero);
            i->draw(*window);
        }
        for (auto& i : gameObject.getGhostspawns()) {
            i->update(time, hero);
            i->draw(*window);
            for (auto& j : i->getGhosts()) {
                gameObject.getGhosts().push_back(&j);
            }
        }
        hero.updatePlayer(time, gameObject.getCharacters());
        hero.updatePlayer(time, gameObject.getGhosts());
        hero.renderShoot(*window);
        gameObject.getGhosts().clear();

        gameObject.getStatusbar()->update(hero);
        gameObject.getStatusbar()->draw(*window);

        for (auto& mine : gameObject.getMines()) {
            mine->explosion(time, hero);
            mine->draw(*window);
        }

        if (hero.getHealth() <= 0) {
            return false;
        }
        if (gameObject.getPortal()->nextLevel(hero))
            return true;
        gameObject.getPortal()->draw(*window);
        hero.draw(*window);
        window->setView(view);
        window->display();
    }
};

void Build::level(float& timeS, UserInfo & data,Player& hero)
{
    if (game(timeS, data, hero)) {
        level(timeS, data, hero);
    }
}

UserInfo Build::dataPlayer(std::string nick) {
    float timeS = 0.f;
    UserInfo data(nick, 0, 0, 0, " ");
    Player hero(sf::Vector2f(0, 0), sf::Vector2f(23, 45), "image/soldat.png");
    level(timeS, data, hero);
    ++data.countGame;
    data.time = std::to_string((int)timeS);
    if (lv == 6) {
        lv = 0;
        ++data.countWin;
        endGame(1);
    }
    else {
        lv = 0;
        ++data.countDeaths;
        endGame(0);
    }
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
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Vector2f pos = window->mapPixelToCoords(pixelPos);
                    int btnNumber = form.checkPressed(pos.x, pos.y);
                    if (btnNumber == 1) {
                        nick = "";
                        flag = true;
                    }
                    if (btnNumber == 2) {
                        UserInfo data = this->dataPlayer(nick);
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

int Build::settings() {
    (*window).setView((*window).getDefaultView());
    (*window).clear();
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
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Vector2f pos = window->mapPixelToCoords(pixelPos);
                    difficulty = form.checkPressed(pos.x, pos.y);
                }
            }
        }
        (*window).clear();
        form.drawSettings(difficulty);
        (*window).display();
    }
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

int Build::endGame(bool typeEnd) {
    (*window).setView((*window).getDefaultView());
    (*window).clear();
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
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
                    sf::Vector2f pos = window->mapPixelToCoords(pixelPos);
                    if (form.checkPressed(pos.x, pos.y) == 3) {
                        this->menu();
                        return 1;
                    }
                }
            }
        }
        (*window).clear();
        form.drawEndLevel(typeEnd);
        (*window).display();
    }
    return 0;
}

