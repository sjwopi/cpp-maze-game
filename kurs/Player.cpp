#include "Player.h"
#include <iostream>

float PX;
float PY;

void Player::positionView(sf::View& view)
{
	float tempX = x, tempY = y;
	if (x < 250)
		tempX = 250;
	if (y < 125)
		tempY = 125;
	if (y > 1275)
		tempY = 1275;
	if (x > 1910)
		tempX = 1910;
	view.setCenter(tempX, tempY);
}

void Player::setWeapon(Weapon* weapon)
{
	this->weapon = weapon;
}

void Player::play(std::string dir, float speed, float time,std::vector<GameObject> Walls,sf::View& view)
{
	sf::FloatRect spriteBounds(sf::Vector2f(sprite.getPosition().x,sprite.getPosition().y), sf::Vector2f(20, 20));

	if (dir == "Left") {
		spriteBounds.left -= 18;
		if (!collision—heck(Walls, spriteBounds)) {
			Move(dir, speed, time);
			positionView(view);
		}
		Move("Right", 0.0001, time);
	}
	else if (dir == "Right") {
		spriteBounds.width += 2;
		if (!collision—heck(Walls, spriteBounds)) {
			Move(dir, speed, time);
			positionView(view);
		}
		Move("Left", 0, time);
	}
	else if (dir == "Up") {
		spriteBounds.top -= 25;
		spriteBounds.width -= 10;
		if (!collision—heck(Walls, spriteBounds)) {
			Move(dir, speed, time);
			positionView(view);
		}
		Move("Down", 0.0001, time);
	}
	else if (dir == "Down") {
		spriteBounds.height += 5;
		spriteBounds.width -= 10;
		if (!collision—heck(Walls, spriteBounds)) {
			Move("Down", speed, time);
			positionView(view);
		}
		Move("Up", 0, time);
	}
}

void Player::Rotation(sf::Vector2f pos)
{
	if (pos.x != PX && pos.y != PY) {
		float Rx = pos.x - x;
		float Ry = pos.y - y;
		PX = pos.x;
		PY = pos.y;
		float rotation = (atan2(Rx, Ry)) * 180 / 3.14159265;
		sprite.setRotation(-rotation);
	}
}

void Player::Move(std::string dir, float speed, float time)
{
	if (dir == "Left") {
		vx = -speed;
		vy = 0;
		frame += 0.01 * time;
		if (frame > 4) frame -= 4;
		sprite.setTextureRect(sf::IntRect((int(frame) * 23), 0, 23, 45));
	}
	if (dir == "Right") {
		vx = speed * 1.3;
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
		vy = speed * 1.3;
		frame += 0.01 * time;
		if (frame > 4) frame -= 4;
		sprite.setTextureRect(sf::IntRect((int(frame) * 23), 0, 23, 45));
	}
	x += vx * time;
	y += vy * time;
	sprite.setPosition(x, y);
}

bool Player::collision—heck(std::vector<GameObject> Walls, sf::FloatRect spriteBounds)
{
	weapon->setWalls(Walls);
	sf::FloatRect wall;
	for (int i = 0; i < Walls.size(); ++i) {
		wall = Walls[i].getGlobalBounds();
		wall.width -= 7;
		wall.left += 5;
		wall.top += 5;
		wall.height -= 7;
		if (wall.intersects(spriteBounds)) {
			return true;
		}
	}
	return false;
}

void Player::updatePlayer(float time, std::vector<Character*>& characters)
{
	update(time);
	weapon->update(time, characters);
	for (auto& i : characters)
		i->update(time);
	if (haveShield) {
		if (healthShield < 0) {
			haveShield = false;
			healthShield = 100;
		}
	}
	else
		healthShield = 100;
}

