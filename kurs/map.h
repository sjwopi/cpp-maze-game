#pragma once
#include "leaf.h"
#include "SFML/Graphics.hpp"
#include <vector>
//Класс который хранит в себе коридоры и комнаты на карте
class Map {
private:
    std::vector<Leaf> leafs;
    std::vector<GameObject> halls;//Коридоры
    std::vector<GameObject> Rooms;//Все комнаты на карте
    std::vector<GameObject> allObjectsOnTheMap;//Комнаты и коридоры
    std::vector<GameObject> Walls;//Стены
    std::vector<sf::Sprite> mapWithTextures;
    sf::Texture textureRoom;
    sf::Texture textureWalls;
    void create_halls(GameObject& const l, GameObject& const r);//Генерация коридоров
    void create_Map(int width, int height);
    void createWalls();
    void createTextures();
    int width = 0;
    int height = 0;
public:
    Map(int width, int height) :width(width), height(height) { create_Map(width, height); createWalls(); createTextures(); }
    Map() {}
    std::vector<GameObject> getAll_Objects_On_The_Map()const { return allObjectsOnTheMap; }
    std::vector<GameObject> getHalls() const{ return halls; }
    std::vector<GameObject> getRooms() const{ return Rooms; }
    std::vector<GameObject> getWalls() const { return Walls; }
    std::vector<sf::Sprite> getMapWithTextures() { return mapWithTextures; }

    sf::Vector2f getRandomCenterRooms()const;

    void draw(sf::RenderWindow& window);
    ~Map() {
        for (auto i : leafs) {
            delete i.leftChild;
            delete i.rightChild;
        }
    }
};