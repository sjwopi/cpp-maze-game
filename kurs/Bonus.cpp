#include "Bonus.h"

Bonus::Bonus(std::string pathTexture, sf::Vector2f position) :GameObject(position, sf::Vector2f(25, 25))
{
	path = pathTexture;
	sprite.setPosition(position);
}

void Bonus::draw(sf::RenderWindow& window)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	window.draw(sprite);
}
