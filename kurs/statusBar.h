#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <string>
class statusBar
{
private:
    sf::Vector2f positionPlayer;
    sf::Vector2f sizeWindow;

    std::string nameTextureHealthIcon;
    std::string nameTextureWeaponIcon;
    std::string nameTextureShieldIcon;

    sf::Texture textureShieldIcon;
    sf::Texture textureHealthIcon;

    sf::Sprite healthIcon;
    sf::Sprite shieldIcon;

    sf::Font font;

    sf::Text shieldHealthText;
    sf::Text weaponText;
    sf::Text healthText;

    int playerHealth = 100;
    int bandolierSize = 0;
    int currentBullets = 0;
    bool isShield = false;
    int sizeBar = 1;
    int healthShield = 0;
public:
    statusBar(sf::RenderWindow& window, std::string nameTextureHealthIcon, std::string nameTextureWeaponIcon, std::string nameTextureShieldIcon, sf::Vector2f positionPlayer, sf::Vector2f sizeWindow);

    void setPlayerHealth(int health) {
        playerHealth = health;
        healthText.setString(std::to_string(playerHealth));
    }
    void setBandolierSize(int bandolierSize) { this->bandolierSize = bandolierSize; }
    void setCurrentBullets(int currentBullets) {
        this->currentBullets = currentBullets;
        weaponText.setString(std::to_string(currentBullets) + "/" + std::to_string(bandolierSize));
    }
    void setNameTextureWeaponIcon(std::string nameTextureWeaponIcon) { this->nameTextureWeaponIcon = nameTextureWeaponIcon; }
    void setHealthShield(int healthShield) {
        this->healthShield = healthShield;
        shieldHealthText.setString(std::to_string(this->healthShield));
    }

    void draw(sf::RenderWindow& window);

    void update(Player& player);
};

