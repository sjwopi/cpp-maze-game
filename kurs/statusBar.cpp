#include "statusBar.h"

statusBar::statusBar(sf::RenderWindow& window, std::string nameTextureHealthIcon, std::string nameTextureWeaponIcon, std::string nameTextureShieldIcon, sf::Vector2f positionPlayer, sf::Vector2f sizeWindow) : nameTextureHealthIcon(nameTextureHealthIcon), nameTextureWeaponIcon(nameTextureWeaponIcon), positionPlayer(positionPlayer), sizeWindow(sizeWindow)
{
    font.loadFromFile("font.ttf");
    weaponText.setFont(font);
    healthText.setFont(font);
    shieldHealthText.setFont(font);
    levelText.setFont(font);

    weaponText.setCharacterSize(10);
    weaponText.setStyle(sf::Text::Bold);
    weaponText.setFillColor(sf::Color::White);

    healthText.setCharacterSize(10);
    healthText.setStyle(sf::Text::Bold);
    healthText.setFillColor(sf::Color::White);

    shieldHealthText.setCharacterSize(10);
    shieldHealthText.setStyle(sf::Text::Bold);
    shieldHealthText.setFillColor(sf::Color::White);

    levelText.setCharacterSize(10);
    levelText.setStyle(sf::Text::Bold);
    levelText.setFillColor(sf::Color::White);

    textureHealthIcon.loadFromFile(nameTextureHealthIcon);
    healthIcon.setTexture(textureHealthIcon);

    textureShieldIcon.loadFromFile(nameTextureShieldIcon);
    shieldIcon.setTexture(textureShieldIcon);
}

void statusBar::draw(sf::RenderWindow& window)
{
    sf::Texture textureWeaponIcon;
    sf::Sprite weaponIcon;
    textureWeaponIcon.loadFromFile(nameTextureWeaponIcon);
    weaponIcon.setTexture(textureWeaponIcon);

    float tempX = positionPlayer.x, tempY = positionPlayer.y;
    if (positionPlayer.x < 250)
        tempX = 250;
    if (positionPlayer.y < 125)
        tempY = 125;
    if (positionPlayer.y > 1275)
        tempY = 1275;
    if (positionPlayer.x > 1910)
        tempX = 1910;
    weaponIcon.setPosition(tempX + (sizeWindow.x / 2) - 75, tempY - (sizeWindow.y / 2) + 6);
    weaponText.setPosition(tempX + (sizeWindow.x / 2) - 40, tempY - (sizeWindow.y / 2) + 7);

    healthIcon.setPosition(tempX + (sizeWindow.x / 2) - 120, tempY - (sizeWindow.y / 2) + 7);
    healthText.setPosition(tempX + (sizeWindow.x / 2) - 100, tempY - (sizeWindow.y / 2) + 7);

    shieldIcon.setPosition(tempX + (sizeWindow.x / 2) - 168, tempY - (sizeWindow.y / 2) + 7);
    shieldHealthText.setPosition(tempX + (sizeWindow.x / 2) - 146, tempY - (sizeWindow.y / 2) + 7);

    levelText.setPosition(tempX - (sizeWindow.x / 2) + 20 , tempY - (sizeWindow.y / 2) + 7);
    if (isShield) {
        window.draw(shieldIcon);
        window.draw(shieldHealthText);
    }

    window.draw(healthIcon);
    window.draw(healthText);

    window.draw(weaponIcon);
    window.draw(weaponText);

    window.draw(levelText);
}

void statusBar::update(Player& player)
{
    setPlayerHealth(player.getHealth());
    setBandolierSize(player.getBandolierSize());
    setCurrentBullets(player.getCurrentBullets());
    positionPlayer = player.getPosition();
    isShield = player.getHaveShield();
    setHealthShield(player.getHealthShield());
}


