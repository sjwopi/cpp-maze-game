#pragma once
#include "Ghost.h"
#include "Character.h"
#include "Player.h"

class GhostSpawn :public Character
{
private:
	float attackRange = 330;
	float timeSpawn = 0;
	std::vector<Ghost> ghosts;
public:
	GhostSpawn(float x, float y, float w, float h, std::string name);
	GhostSpawn(sf::Vector2f, sf::Vector2f, std::string name);
	void update(float time, Player&);
	void draw(sf::RenderWindow& window);
	std::vector<Ghost>& getGhosts() { return ghosts; }
	void setAttackRange(float attackRange) { this->attackRange = attackRange; }
};

