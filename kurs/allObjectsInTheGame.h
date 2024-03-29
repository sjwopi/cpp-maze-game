#pragma once
#include "shieldBonus.h"
#include "BulletBonus.h"
#include "HealthBonus.h"
#include "WeaponBonus.h"
#include "map.h"
#include "Turel.h"
#include "Player.h"
#include "map.h"
#include "Gun.h"
#include "statusBar.h"
#include "Machine.h"
#include "GhostSpawn.h"
#include "Mine.h"
#include "Portal.h"

class allObjectsInTheGame
{
public:
	allObjectsInTheGame() {}
	void �reate(sf::RenderWindow& window, int widthMap, int heightMap, int countTurels, int countGhostspawns, int countHealthBonuses, int countBulletsBonuses, int countShieldBonuses,int countMines);
	Map* getMap() { return map; }
	Gun* getGun() { return gun; }
	Portal* getPortal() { return portal; }
	Machine* getMachine(){ return machine; }
	WeaponBonus* getWeaponBonus() { return weaponBonus; }
	std::vector<Bonus*>& getAllBonuses() { return allBonuses; }
	std::vector<Mine*>& getMines() { return mines; }
	std::vector<Character*>& getCharacters(){ return characters; }
	std::vector<Turel*>& getTurels() { return turels; }
	std::vector<GhostSpawn*>& getGhostspawns() { return ghostspawns; }
	std::vector<Character*>& getGhosts() { return ghosts; }
	statusBar* getStatusbar() { return statusbar; }
	~allObjectsInTheGame();
private:
	Portal* portal;
	Map* map;
	Gun* gun;
	Machine* machine;
	WeaponBonus* weaponBonus;
	std::vector<Bonus*> allBonuses;
	std::vector<Mine*> mines;
	std::vector<Character*> characters;
	std::vector<Turel*> turels;
	std::vector<GhostSpawn*> ghostspawns;
	std::vector<Character*> ghosts;
	statusBar* statusbar;
	sf::RenderWindow* window;
};

