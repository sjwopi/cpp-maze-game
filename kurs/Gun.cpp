#include "Gun.h"

bool Gun::fire(sf::Vector2f direction, sf::Vector2f coordinatePlayer)
{
    if (fireTimer > 100.f && currentBullets > 0) {
        Bullet bullet(direction, coordinatePlayer, 3);

        Bandolier.push_back(bullet);
        --currentBullets;
        fireTimer = 0.f;

        return true;
    }
    else if (currentBullets <= 0)
        reload();
    return false;
}
