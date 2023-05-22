#define _USE_MATH_DEFINES
#include <cmath>
#include "Turel.h"
#include "Player.h"


void Turel::Rotation(sf::Vector2f pos)
{
		float Rx = pos.x - x;
		float Ry = pos.y - y;
		float rotation = (atan2(Rx, Ry)) * 180 / 3.14159265;
		sprite.setRotation(-rotation);
}

Turel::Turel(float x, float y, float w, float h, std::vector<GameObject> Walls, std::string name) :Character(x, y, w, h), Weapon(name, 6, 20, 30000)
{
    std::vector<GameObject> wallsAroundTheTurret;
    for (const auto& i : Walls) {
        if (i.getPosition().x - x < 300 && i.getPosition().y - y < 300)
            wallsAroundTheTurret.push_back(i);
    }
    setWalls(wallsAroundTheTurret);
    setSpriteLoadFromFile(name);
    sprite.setTextureRect(sf::IntRect(30, 41, -30, -41));
    sprite.setOrigin(w / 2, h / 2);
}

Turel::Turel(sf::Vector2f position, sf::Vector2f size, std::vector<GameObject> Walls, std::string name) :Character(position, size), Weapon(name, 6, 20, 30000)
{
    std::vector<GameObject> wallsAroundTheTurret;
    for (const auto& i : Walls) {
        if (i.getPosition().x - x < 300 && i.getPosition().y - y < 300)
            wallsAroundTheTurret.push_back(i);
    }
    setWalls(wallsAroundTheTurret);
    setSpriteLoadFromFile(Weapon::path);
    sprite.setTextureRect(sf::IntRect(30, 41, -30, -41));
    sprite.setOrigin(size.x / 2, size.y / 2);
}

void Turel::draw(sf::RenderWindow& window)
{
    if (!isDead) {
        window.draw(sprite);
        render(window);
        sf::Texture textureHealth;
        if (health > 80)
            textureHealth.loadFromFile("image/fullhp.png");
        else if (health > 60)
            textureHealth.loadFromFile("image/80hp.png");
        else if (health > 40)
            textureHealth.loadFromFile("image/60hp.png");
        else if (health > 20)
            textureHealth.loadFromFile("image/40hp.png");
        else if (health > 0)
            textureHealth.loadFromFile("image/20hp.png");
        sf::Sprite healthBar;
        healthBar.setTexture(textureHealth);
        healthBar.setPosition(x - 15, y - 30);
        window.draw(healthBar);
    }
    else {
        texture.loadFromFile("image/razrushenie.png");
        sprite.setTexture(texture);
        window.draw(sprite);
    }
}

bool Turel::fire(sf::Vector2f direction, sf::Vector2f coordinatePlayer)
{
    if (sqrt(pow(coordinatePlayer.x - direction.x, 2) + pow(coordinatePlayer.y - direction.y, 2)) <= 280) {
        if (fireTimer > 200.f && currentBullets > 0 && !isDead) {
            Rotation(direction);
            sf::Vector2f aimDirNorm = (direction - coordinatePlayer) / (float)sqrt(pow((coordinatePlayer - direction).x - 20, 2) + pow((coordinatePlayer - direction).y - 20, 2));
            Bullet bullet(aimDirNorm, coordinatePlayer, 2);

            Bandolier.push_back(bullet);
            --currentBullets;
            fireTimer = 0.f;

            return true;
        }
        if (!currentBullets && fireTimer > 1400.f) {
            currentBullets = maxBullets;
        }
    }
    return false;
}

void Turel::update(float time, Player& player)
{
    sf::FloatRect characterBounds(player.getPosition(), player.getSize());
    fireTimer += time;
    if (!isDead) {
        for (auto& bullet : Bandolier) {
            bullet.update(time);
            if (bullet.getShape().getGlobalBounds().intersects(characterBounds)) {
                Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
                if (!player.getHaveShield())
                    player.reduceHealth(damage);
                else
                    player.reduceHealthShield(damage * 2);
            }
            player.update(time);
            if (sqrt(pow(x - bullet.getShape().getPosition().x, 2) + pow(y - bullet.getShape().getPosition().y, 2)) > 280) {
                Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
            }
            for (const auto& wall : Walls) {
                if (bullet.checkBulletWallCollision(wall)) {
                    Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
                    break;
                }
            }
        }
    }
}





