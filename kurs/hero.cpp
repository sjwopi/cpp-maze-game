#include "hero.h"
void Hero::Move(std::string dir, float speed, float time)
{
	if (dir == "Left") {
		vx = -speed;
		vy = 0;
		frame += 0.01 * time;
		if (frame > 4) frame -= 4;
		sprite.setTextureRect(sf::IntRect((int(frame) * 23), 0, 23, 45));
	}
	if (dir == "Right") {
		vx = speed;
		vy = 0;
		frame += 0.01 * time;
		if (frame > 4) frame -= 4;
		sprite.setTextureRect(sf::IntRect((int(frame) * 23), 0, 23, 45));
	}
	if (dir == "Up") {
		vx = 0;
		vy = -speed;
		frame += 0.01 * time;
		if (frame > 4) frame -= 4;
		sprite.setTextureRect(sf::IntRect((int(frame) * 23), 0, 23, 45));
	}
	if (dir == "Down") {
		vx = 0;
		vy = speed;
		frame += 0.01 * time;
		if (frame > 4) frame -= 4;
		sprite.setTextureRect(sf::IntRect((int(frame) * 23), 0, 23, 45));
	}
	x += vx * time;
	y += vy * time;
	sprite.setPosition(x, y);
}
sf::RectangleShape Hero::Check_for_colic(std::vector<sf::RectangleShape> Walls, sf::FloatRect spriteBounds)
{
	sf::RectangleShape kolizion(sf::Vector2f(30, 30));
	kolizion.setPosition(-100, 0);
	sf::FloatRect wall;
	for (int i = 0; i < Walls.size(); ++i) {
		wall = Walls[i].getGlobalBounds();
		wall.width -= 7;
		wall.left += 5;
		wall.top += 5;
		wall.height -= 7;
		if (wall.intersects(spriteBounds)) {
			kolizion.setPosition(Walls[i].getPosition());
			return kolizion;
		}
	}
	return kolizion;
}