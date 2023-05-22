#pragma once
#include "Player.h"
#include "GameObject.h"
class Portal : public GameObject {
public:
	Portal(sf::Vector2f pos, int width, int height, std::string path_texture):GameObject(pos.x,pos.y,width,height){
        path = path_texture;
        texture.loadFromFile(path);
        sprite.setTexture(texture);
    }
    bool nextLevel(Player& player) {
        if (player.intersects(getGlobalBounds())) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                return true;
        }
        return false;
    }
    void draw(sf::RenderWindow& window) { window.draw(sprite); }
};
