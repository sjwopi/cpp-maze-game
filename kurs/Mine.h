#pragma once
#include "Player.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"

class Mine :public GameObject
{
private:
	int damage = 40;
	bool isExploded = false;
	float time = 250;
public:
	Mine(sf::Vector2f position, sf::Vector2f size, std::string name) :GameObject(position, size) { setSpriteLoadFromFile(name); }
	void explosion(float time, Player& player);
	void draw(sf::RenderWindow& window);
};

