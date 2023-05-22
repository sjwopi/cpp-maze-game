#pragma once
#include <string>
#include "Character.h"
#include "Player.h"
class Ghost:
	public Character
{
private:
	float speed = 0;
	int damage = 4;
public:
	Ghost(int x, int y, int w, int h, float speed, std::string path_texture) :Character(x, y, w, h), speed(speed) {
		path = path_texture; 
		sprite.setPosition(x, y);
		sprite.setColor(sf::Color(170, 170, 170));
		health = 10;
	}
	void update(float time, Player& player);
	void draw(sf::RenderWindow& window);
	
	int getDamage()const { return damage; }

	bool operator==(const Ghost& other);
};

