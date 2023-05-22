#pragma once
#include <iostream>
#include "Weapon.h"
#include "Character.h"
#include <string>

class Gun :
    public Weapon
{
public:
    Gun(std::string path_name) :Weapon(path_name, 10, 8, 30) {}
    bool fire(sf::Vector2f direction, sf::Vector2f coordinatePlayer)override;
};

