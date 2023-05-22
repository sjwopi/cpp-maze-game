#include "allObjectsInTheGame.h"

void allObjectsInTheGame::ñreate(sf::RenderWindow& window, int widthMap, int heightMap, int countTurels, int countGhostspawns, int countHealthBonuses, int countBulletsBonuses, int countShieldBonuses, int countMines)
{
    this->window = &window;
    map = new Map(widthMap, heightMap);
    statusbar = new statusBar(*(this->window), "image/Health.png", "image/Gun.png", "image/shield.png", map->getRandomCenterRooms(), sf::Vector2f(500, 250));
    gun = new Gun("image/Gun.png");
    machine = new Machine("image/machine.png");
    weaponBonus = new WeaponBonus(machine->getPathTexture(), map->getRandomCenterRooms(), machine);
    portal = new Portal(map->getRandomCenterRooms(), 20, 20,"image/portal.png");

    for (int i = 0; i < countShieldBonuses; ++i) {
        shieldBonus* shieldbonus = new shieldBonus("image/shield.png", map->getRandomCenterRooms());
        allBonuses.push_back(shieldbonus);
    }
    for (int i = 0; i < countHealthBonuses; ++i) {
        HealthBonus* healthbonus = new HealthBonus("image/HealthBonus.png", map->getRandomCenterRooms());
        allBonuses.push_back(healthbonus);
    }
    for (int i = 0; i < countBulletsBonuses; ++i) {
        BulletBonus* bulletsBonus = new BulletBonus("image/Ammo.png", map->getRandomCenterRooms());
        allBonuses.push_back(bulletsBonus);
    }

    for (int i = 0; i < countGhostspawns; ++i) {
        GhostSpawn* ghostspawn = new GhostSpawn(map->getRandomCenterRooms(), sf::Vector2f(35, 35), "image/spavner.png");
        characters.push_back(ghostspawn);
        ghostspawns.push_back(ghostspawn);
    }
    for (int i = 0; i < countTurels; ++i) {
        Turel* turel = new Turel(map->getRandomCenterRooms(), sf::Vector2f(35, 41), map->getWalls(), "image/3.png");
        characters.push_back(turel);
        turels.push_back(turel);
    }
    for (int i = 0; i < countMines; ++i) {
        Mine* mine = new Mine(map->getRandomCenterRooms(), sf::Vector2f(18, 19), "image/mine.png");
        mines.push_back(mine);
    }
}

allObjectsInTheGame::~allObjectsInTheGame()
{
    delete map;
    delete statusbar;
    delete gun;
    delete machine;
    delete weaponBonus;
    delete portal;
    for (auto& i : allBonuses) {
        delete i;
    }
    for (auto& i : characters) {
        delete i;
    }
}
