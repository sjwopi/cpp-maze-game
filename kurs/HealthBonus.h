#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bonus.h"


class HealthBonus :
    public Bonus
{
public:
    HealthBonus(std::string pathTexture, sf::Vector2f position) :Bonus(pathTexture, position) {}
    void apply(Player& player)override {
        if (player.getHealth() + 50 > 100)
            player.setHealth(100);
        else
            player.setHealth(player.getHealth() + 50);
        taken = true;
    }
};

