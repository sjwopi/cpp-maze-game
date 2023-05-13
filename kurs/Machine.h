#pragma once
#include "Weapon.h" 
class Machine :public Weapon
{
public:
    Machine(std::string path_name) :Weapon(path_name, 7, 28, 100) {}
    bool fire(sf::Vector2f direction, sf::Vector2f coordinatePlayer)override;
};

