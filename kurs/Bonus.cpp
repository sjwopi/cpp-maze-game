#include "Bonus.h"

Bonus::Bonus(std::string pathTexture, sf::Vector2f position) :pathTexture(pathTexture), position(position)
{
	sprite.setPosition(position);
}

void Bonus::draw(sf::RenderWindow& window)
{
	sf::Texture texture;
	texture.loadFromFile(pathTexture);
	sprite.setTexture(texture);
	window.draw(sprite);
}

void Bonus::setPosition(sf::Vector2f position)
{
	this->position = position;
	sprite.setPosition(position);
}
