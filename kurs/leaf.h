#pragma once
#include <iostream>
#include <vector>
#include "GameObject.h"
class Leaf : public GameObject
{
public:
    Leaf(int x, int y, int width, int height) :GameObject(x, y, width, height) {}
    Leaf* leftChild = nullptr;
    Leaf* rightChild = nullptr;
    bool Split_into_leaves();//–азбиение на листь€
    void CreateRoom();//—оздание комнат
    GameObject room;// омната внутри этого листа
    int Get_MIN_LEAF_SIZE() { return MIN_LEAF_SIZE; }
    int Get_MAX_LEAF_SIZE() { return MAX_LEAF_SIZE; }
    ~Leaf() {}
private:
    int const MIN_LEAF_SIZE = 175; //минимальный размер листа(175)
    int const MAX_LEAF_SIZE = 250; //максимальный размер листа(250)
};

