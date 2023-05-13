#pragma once
#include "Player.h"
#include "SFML/Graphics.hpp"

class Bonus {
public:
    Bonus(std::string pathTexture, sf::Vector2f position);
    virtual ~Bonus() {};

    virtual void apply(Player& player) = 0;
    virtual void draw(sf::RenderWindow& window);

    bool isTaken() const { return taken; }
    sf::FloatRect getGlobalBounds() const { return sf::FloatRect(position, sf::Vector2f(25, 25)); }

    void setPosition(sf::Vector2f);
protected:
    sf::Sprite sprite;
    bool taken = false;
    std::string pathTexture;
    sf::Vector2f position;
};
