#pragma once
#include <SFML/Graphics.hpp>

class Form
{
private:
	sf::RenderWindow* window;
	sf::Sprite fon;
	sf::Texture fonTexture;
	sf::Font font;
	
	sf::RectangleShape btn[3];
	sf::Text text[4];
public:
	Form(float width, float height, sf::RenderWindow& window);

	void drawMenu();
	void drawLogin(std::string nick);
	void drawSettings();
	int checkPressed(double x, double y);
};