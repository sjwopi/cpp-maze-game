#pragma once
#include<SFML/Graphics.hpp>
#include "GameObject.h"
#include <string>
#include <cmath>
#include "Weapon.h";
#include "Character.h"
#include "Gun.h"

class Player :public Character{
private:
	Weapon* weapon = nullptr;
	bool haveShield = false;
	int healthShield = 0;
	float vx = 0, vy = 0, frame = 0;
	void positionView(sf::View& view);
	void Move(std::string dir, float speed, float time);
	bool flag = true;
public:
	Player(float x, float y, float w, float h, std::string name) : Character(x, y, w, h){
		setSpriteLoadFromFile(name);
		setColor(170, 170, 170);
		sprite.setOrigin(12, 14);
	}
	Player(sf::Vector2f position, sf::Vector2f size,std::string name) :Character(position, size) {
		setSpriteLoadFromFile(name);
		setColor(170, 170, 170);
		sprite.setOrigin(12, 14);
	}
	void setWeapon(Weapon* weapon);
	void setBandolierSize(int bandolierSize) { weapon->setBandolierSize(weapon->getBandolierSize() + bandolierSize); }

	Weapon* getWeapon()const { return weapon; }
	int getBandolierSize()const { return weapon->getBandolierSize(); }
	int getCurrentBullets()const { return weapon->getBullets(); }
	float getRotation()const { return sprite.getRotation(); }
	std::string getPathWeapon()const { return weapon->getPathTexture(); }
	bool getHaveShield()const { return haveShield; }
	int getHealthShield()const { return healthShield; }

	void play(std::string dir, float speed, float time, std::vector<GameObject> Walls,sf::View& view);
	void Rotation(sf::Vector2f pos);
	void setShield(bool haveShield) { this->haveShield = haveShield; healthShield = 100; }
	void reduceHealthShield(int damage) { healthShield -= damage; }

	bool collision—heck(std::vector<GameObject> Walls, sf::FloatRect spriteBounds);

	bool intersects(const sf::FloatRect globalBounds)const { return sprite.getGlobalBounds().intersects(globalBounds); }

	void shoot(float time,sf::Vector2f direction,sf::Vector2f coordinatePlayer) {
		weapon->fire(direction,coordinatePlayer);
	}
	void updatePlayer(float time, std::vector<Character*>& characters);
	void renderShoot(sf::RenderWindow& window) {
		weapon->render(window);
	}
	void reload() { weapon->reload(); }
	void draw(sf::RenderWindow& window) { window.draw(sprite); }
};