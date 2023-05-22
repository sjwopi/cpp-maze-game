#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Character.h"
class Weapon
{
public:
    Weapon(std::string path_name, int damage, int maxBullets,int bandolierSize):path(path_name),damage(damage),maxBullets(maxBullets),currentBullets(maxBullets), bandolierSize(bandolierSize){}
    virtual ~Weapon() {}

    virtual bool fire(sf::Vector2f,sf::Vector2f) = 0;
    void reload() { 
        if (!isReloading && bandolierSize > 0 && currentBullets < maxBullets) {
            isReloading = true;
            reloadingTime = 450;
        }
    }
    virtual void update(float time, std::vector<Character*>&);
    void render(sf::RenderWindow& window) {
        for (auto& i : Bandolier) {
            i.draw(&window);
        }
    }

    std::string getPathTexture()const { return path; }

    int getBullets() const { return currentBullets; }
    int getBandolierSize()const { return bandolierSize; }

    void setBandolierSize(int bandolierSize) { this->bandolierSize = bandolierSize; }
    void setWalls(const std::vector<GameObject>& Walls) { this->Walls = Walls; }
protected:
    bool isReloading = false;
    float reloadingTime = 0.0;
    std::string path;
    int damage = 0;
    int maxBullets = 0;
    int currentBullets = 0;
    int bandolierSize = 0;
    float fireTimer = 0;
    std::vector<Bullet> Bandolier;
    std::vector<GameObject> Walls;
};

