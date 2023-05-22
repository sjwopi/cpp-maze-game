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
    bool Split_into_leaves();//��������� �� ������
	void CreateRoom();//�������� ������
	GameObject room;//������� ������ ����� �����
    int get_MIN_LEAF_SIZE() { return MIN_LEAF_SIZE; }
    int get_MAX_LEAF_SIZE() { return MAX_LEAF_SIZE; }
private:
    int const MIN_LEAF_SIZE = 175; //����������� ������ �����(175)
    int const MAX_LEAF_SIZE = 250; //������������ ������ �����(250)
};

