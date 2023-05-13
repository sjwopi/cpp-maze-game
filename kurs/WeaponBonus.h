#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bonus.h"
#include "Weapon.h"

class WeaponBonus :
    public Bonus
{
public:
    WeaponBonus(std::string pathTexture, sf::Vector2f position, Weapon* weapon) :Bonus(pathTexture, position), weapon(weapon) {}
    void apply(Player& player)override {
        if (timeTakingBonus > 200) {
            Weapon* temp = player.getWeapon();
            pathTexture = player.getPathWeapon();
            player.setWeapon(weapon);
            weapon = temp;
            timeTakingBonus = 0;
        }
    }
    void update(float time) {
        timeTakingBonus += time;
    }
    void draw(sf::RenderWindow& window)override {
        sf::Sprite spriteWeapon;
        spriteWeapon.setPosition(position);
        sf::Texture textureWeapon;
        textureWeapon.loadFromFile(pathTexture);
        spriteWeapon.setTexture(textureWeapon);
        window.draw(spriteWeapon);
    }
private:
    float timeTakingBonus = 0;
    Weapon* weapon;
};