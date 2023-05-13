#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include <string>
class Bullet {
private:
    sf::Texture texture_for_bullet;
    sf::CircleShape shape;
    sf::Vector2f direction = { 0.f,0.f };
    float maxspeed = 1.8;
public:
    sf::CircleShape& getShape() { return shape; }
    Bullet(sf::Vector2f direction, sf::Vector2f coordinatePlayer, float maxspeed, float radius = 1.8) :direction(direction), maxspeed(maxspeed) {
        shape.setRadius(radius);
        shape.setOrigin(radius, radius);
        shape.setPosition(coordinatePlayer);
        shape.setFillColor(sf::Color(sf::Color::Black));
    }
    void update(float time) { shape.move(direction * maxspeed * time); }
    void draw(sf::RenderWindow* window) {
        window->draw(shape);
    }
    bool checkBulletWallCollision(const GameObject& wall)const {
        return shape.getGlobalBounds().intersects(wall.getGlobalBounds());
    }
    bool operator==(const Bullet& other) {
        return this == &other;
    }
};
