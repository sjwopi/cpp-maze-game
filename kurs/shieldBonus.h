#pragma once
#include "Player.h"
#include "Bonus.h"

class shieldBonus :
	public Bonus {
public:
	shieldBonus(std::string pathTexture, sf::Vector2f position) :Bonus(pathTexture, position) {}
	void apply(Player& player)override { player.setShield(true); taken = true; }
};