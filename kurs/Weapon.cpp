#include "Weapon.h"

void Weapon::update(float time, std::vector<Character*>& characters)
{
    fireTimer += time;
    for (auto& bullet : Bandolier) {
        bullet.update(time);
        for (auto& i : characters) {
            if (!i->getIsDead()) {
                sf::FloatRect characterBounds = i->getGlobalBounds();
                characterBounds.left -= 10.f;
                characterBounds.top -= 10.f;
                characterBounds.width += 20.f;
                characterBounds.height += 20.f;
                if (bullet.getShape().getGlobalBounds().intersects(characterBounds)) {
                    Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
                    i->reduceHealth(damage);
                }
            }
        }
        for (const auto& wall : Walls) {
            if (bullet.checkBulletWallCollision(wall)) {
                Bandolier.erase(std::remove(Bandolier.begin(), Bandolier.end(), bullet), Bandolier.end());
                break;
            }
        }
    }
    if (isReloading) {
        reloadingTime -= time;
        if (reloadingTime <= 0.0f) {
            isReloading = false;
            int bulletsToReload = std::min(maxBullets - currentBullets, bandolierSize);
            bandolierSize -= bulletsToReload;
            currentBullets += bulletsToReload;
        }
    }
}
