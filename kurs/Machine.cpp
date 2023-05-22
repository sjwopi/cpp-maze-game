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

//void Machine::update(float time, std::vector<Character*> characters)
//{
//    fireTimer += time;
//    for (auto& bullet : Bandolier) {
//        bullet.update(time);
//        for (auto& i : characters) {
//            if (!i->getIsDead()) {
//                sf::FloatRect characterBounds(i->getPosition(), i->getSize());
//                if (bullet.getShape().getGlobalBounds().intersects(characterBounds)) {
//                    Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
//                    i->reduceHealth(damage);
//                }
//            }
//        }
//        for (const auto& wall : Walls) {
//            if (bullet.checkBulletWallCollision(wall)) {
//                Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
//                break;
//            }
//        }
//    }
//    if (isReloading) {
//        reloadingTime -= time;
//        if (reloadingTime <= 0.0f) {
//            isReloading = false;
//            int bulletsToReload = std::min(maxBullets - currentBullets, bandolierSize);
//            bandolierSize -= bulletsToReload;
//            currentBullets += bulletsToReload;
//        }
//    }
//}

//void Machine::render(sf::RenderWindow& window)
//{
//    for (auto& Bullet : Bandolier) {
//        Bullet.draw(&window);
//    }
//}
