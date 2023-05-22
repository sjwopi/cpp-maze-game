#include "GhostSpawn.h"
#include <iostream>

GhostSpawn::GhostSpawn(float x, float y, float w, float h, std::string name):Character(x,y,w,h)
{
    path = name;
    sprite.setPosition(x, y);
}

GhostSpawn::GhostSpawn(sf::Vector2f position, sf::Vector2f size, std::string name) :Character(position, size)
{
    path = name;
    sprite.setPosition(x, y);
}

void GhostSpawn::update(float time, Player& player)
{
    if (!isDead) {
        sf::Vector2f direction = player.getPosition() - sf::Vector2f(x, y);
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        sf::FloatRect characterBounds(player.getPosition(), player.getSize());


        timeSpawn += time;

        if (distance < attackRange && timeSpawn > 350.f) {
            Ghost ghost(x, y, 25, 25, 0.25, "image/Ghost.png");
            ghosts.push_back(ghost);
            timeSpawn = 0.f;
        }
        for (auto& ghost : ghosts) {
            ghost.update(time, player);
            if (ghost.getGlobalBounds().intersects(characterBounds)) {
                ghosts.erase(std::remove(ghosts.begin(), ghosts.end(), ghost), ghosts.end());
                if (!player.getHaveShield())
                    player.reduceHealth(ghost.getDamage());
                else
                    player.reduceHealthShield(ghost.getDamage() * 2);
            }
            if (ghost.getHealth() < 0) {
                ghosts.erase(std::remove(ghosts.begin(), ghosts.end(), ghost), ghosts.end());
            }
        }
        player.update(time);
    }
}

void GhostSpawn::draw(sf::RenderWindow& window)
{
    if (!isDead) {
        texture.loadFromFile(path);
        sprite.setTexture(texture);
        window.draw(sprite);
        for (auto& ghost : ghosts) {
            ghost.draw(window);
        }
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
        healthBar.setPosition(x + 2, y - 10);
        window.draw(healthBar);
    }
}

