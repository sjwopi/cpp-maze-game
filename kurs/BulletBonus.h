#pragma once
#include "SFML/Graphics.hpp"
#include "Bonus.h"
#include "Player.h"

class BulletBonus :
    public Bonus
{
public:
    BulletBonus(std::string pathTexture, sf::Vector2f position) :Bonus(pathTexture, position) {}
    void apply(Player& player)override {
        player.setBandolierSize(50);
        taken = true;
    }
};