#pragma once
#include "SFML/Graphics.hpp"

#define MAX_ITEMS 3

class Login
{
public:
	Login(float width, float height);

	void draw(sf::RenderWindow& window, std::string nick);
	int checkPressed(double x, double y);
	sf::RectangleShape login[MAX_ITEMS];
};