#pragma once
#include "GameObject.h"
#include "Weapon.h"
#include <string>
#include "Player.h"
#include "Character.h"
class Turel : virtual public Weapon, public Character
{
private:
	void Rotation(sf::Vector2f pos);
public:
	Turel(float x, float y, float w, float h, std::vector<GameObject> Walls, std::string name);
	Turel(sf::Vector2f position, sf::Vector2f size, std::vector<GameObject> Walls, std::string name);
	bool fire(sf::Vector2f direction, sf::Vector2f coordinatePlayer)override;
	void update(float time, Player& player);
	void draw(sf::RenderWindow& window);
};

