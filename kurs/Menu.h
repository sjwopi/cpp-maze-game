#pragma once
#include "SFML/Graphics.hpp"

#define MAX_ITEMS 3

class Menu
{
public:
	Menu(float width, float height);

	void draw(sf::RenderWindow& window);
	int checkPressed(double x, double y);

	sf::RectangleShape menu[MAX_ITEMS];
	//sf::Text text[MAX_ITEMS];
};