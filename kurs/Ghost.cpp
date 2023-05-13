#include "Ghost.h"

void Ghost::update(float time, Player& player)
{
    sf::Vector2f direction = player.getPosition() - sprite.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction = direction / distance;
    sf::Vector2f velocity = direction * speed;
    sprite.setPosition(sprite.getPosition() + velocity * time);
    x = sprite.getPosition().x;
    y = sprite.getPosition().y;
    if (player.getPosition().x > x) {
        sprite.setTextureRect(sf::IntRect(25, 0, -25, 25));
    }
    else {
        sprite.setTextureRect(sf::IntRect(0, 0, 25, 25));
    }
}

void Ghost::draw(sf::RenderWindow& window)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
    window.draw(sprite);
}

bool Ghost::operator==(const Ghost& other)
{
    return this == &other;
}
