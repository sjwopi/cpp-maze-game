#include "leaf.h"
int random2(int min, int max) {
    return (min + (rand() % (max - min + 1)));
}
//��������� �� ������
bool Leaf::Split_into_leaves()
{
    if (leftChild != nullptr || rightChild != nullptr)
        return false;
    bool splitH = (0.1 * (rand() % 11)) > 0.5;
    if (width > height && (width / height) >= 1.25)
        splitH = false;
    else if (height > width && (height / width) >= 1.25)
        splitH = true;
    int max = (splitH ? height : width) - MIN_LEAF_SIZE; // ���������� ������������ ������ ��� ������
    if (max <= MIN_LEAF_SIZE)
        return false;
    int split = rand() % (max - MIN_LEAF_SIZE + 1) + MIN_LEAF_SIZE; // ������������, ��� ����� ���������
    if (splitH) {
        leftChild = new Leaf(x, y, width, split);
        rightChild = new Leaf(x, y + split, width, height - split);
    }
    else {
        leftChild = new Leaf(x, y, split, height);
        rightChild = new Leaf(x + split, y, width - split, height);
    }
    return true;
}
//�������� ������
void Leaf::CreateRoom()
{
    if (leftChild != nullptr || rightChild != nullptr)
    {
        // ���� ���� ��� ��������, ������� ��������� � ��� �������� �������
        if (leftChild != nullptr)
        {
            (*leftChild).CreateRoom();
        }
        if (rightChild != nullptr)
        {
            (*rightChild).CreateRoom();
        }
    }
    else
    {
        // ���� ���� ����� � �������� �������
        int Size_Room_width = random2(90, width - 70);
        int Size_Room_heigth = random2(90, height - 70);
        // ����������� ������� ������ �����, �� �� �������� � ����� 
        // ����� �� �������� ����� (����� ������� ��������)
        int Room_pos_x = random2(30, width - Size_Room_width - 30);
        int Room_pos_y = random2(30, height - Size_Room_heigth - 30);
        Room_pos_x += x;
        Room_pos_y += y;
        room.setPosition(Room_pos_x, Room_pos_y);
        room.setSize(Size_Room_width, Size_Room_heigth);
    }
}