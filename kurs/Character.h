#pragma once
#include"GameObject.h"
class Character :public GameObject {
protected:
	int health;
	float gameTime = 0;
	bool isDead = false;
public:
	Character(float x, float y, float w, float h) :GameObject(x, y, w, h), health(100) {}
	Character(sf::Vector2f position, sf::Vector2f size) :GameObject(position, size), health(100) {}
	void reduceHealth(int bulletDamage) { health -= bulletDamage; sprite.setColor(sf::Color(100, 0, 0)); }
	void restoreHealth(int health) { this->health += health; }

	int getHealth()const { return health; }
	bool getIsDead()const { return isDead; }

	void setHealth(int health) { this->health = health; }
	void update(float time) {
		gameTime += time;
		if (gameTime > 300) {
			sprite.setColor(sf::Color(170, 170, 170));
			gameTime = 0;
		}
	}
};