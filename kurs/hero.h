#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "GameObject.h"
class Hero : public GameObject {
protected:
	unsigned int health = 100;
	float w = 0, h = 0, vx = 0, vy = 0, frame = 0;
public:
	Hero(float x, float y, float w, float h) :GameObject(x, y, w, h) {}
	void Move(std::string dir, float speed, float time);
	//virtual void Rotation(sf::Vector2f pos, float time) = 0;
	sf::RectangleShape Check_for_colic(std::vector<sf::RectangleShape> Walls, sf::FloatRect spriteBounds);
	virtual void Play(std::string dir, float speed, float time, std::vector<sf::RectangleShape> Walls, sf::View&) {};
};