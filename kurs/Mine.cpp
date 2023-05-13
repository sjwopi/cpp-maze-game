#include "Mine.h"

void Mine::explosion(float time, Player& player)
{
	if (player.intersects(getGlobalBounds()) && !isExploded) {
		if (player.getHaveShield()) {
			player.reduceHealth(damage / 2);
			player.reduceHealthShield(damage);
		}
		else
			player.reduceHealth(damage);
		isExploded = true;
	}
	if (isExploded)
		this->time -= time;
}

void Mine::draw(sf::RenderWindow& window)
{
	if (!isExploded)
		window.draw(sprite);
	else if (time > 0) {
		sf::Sprite sprite;
		sf::Texture texture;
		texture.loadFromFile("image/boom.png");
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		window.draw(sprite);
	}
}
