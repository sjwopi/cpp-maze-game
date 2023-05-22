#pragma once
#include "Player.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"

class Bonus : public GameObject{
public:
    Bonus(std::string pathTexture, sf::Vector2f position);

    virtual void apply(Player& player) = 0;
    virtual void draw(sf::RenderWindow& window);

    bool isTaken() const { return taken; }
protected:
    bool taken = false;
};
