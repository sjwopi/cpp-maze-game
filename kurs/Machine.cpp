#include "Machine.h"

bool Machine::fire(sf::Vector2f direction, sf::Vector2f coordinatePlayer)
{
    if (fireTimer > 50.f && currentBullets > 0) {
        Bullet bullet(direction, coordinatePlayer, 4);

        Bandolier.push_back(bullet);
        --currentBullets;
        fireTimer = 0.f;

        return true;
    }
    else if (currentBullets <= 0)
        reload();
    return false;
}