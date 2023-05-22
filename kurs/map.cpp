#include "map.h"
int randomIntforMap(int min, int max) {
    return (min + (rand() % (max - min + 1)));
}
void Map::create_halls(GameObject& const l, GameObject& const r)
{
    int Rarr = 20;
    int Rarr1 = 50;
    std::pair<int, int> point1;
    point1.first = randomIntforMap(l.getPosition().x + Rarr, (l.getPosition().x + l.getSize().x) - Rarr1);
    point1.second = randomIntforMap(l.getPosition().y + Rarr, (l.getPosition().y + l.getSize().y) - Rarr1);
    std::pair<int, int> point2;
    point2.first = randomIntforMap(r.getPosition().x + Rarr, (r.getPosition().x + r.getSize().x) - Rarr1);
    point2.second = randomIntforMap(r.getPosition().y + Rarr, (r.getPosition().y + r.getSize().y) - Rarr1);
    int w = point2.first - point1.first;
    int h = point2.second - point1.second;
    GameObject hall;
    int SIZE = 35;//20 30
    if (w < 0)
    {
        if (h < 0)
        {
            if ((0.1 * (rand() % 11)) < 0.5)
            {
                hall.setPosition(point2.first, point1.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point2.first, point2.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
            else
            {
                hall.setPosition(point2.first, point2.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point1.first, point2.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
        }
        else if (h > 0)
        {
            if ((0.1 * (rand() % 11)) < 0.5)
            {
                hall.setPosition(point2.first, point1.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point2.first, point1.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
            else
            {
                hall.setPosition(point2.first + SIZE, point2.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point1.first, point1.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
        }
        else // если (h == 0)
        {
            hall.setPosition(point2.first, point2.second);
            hall.setSize(abs(w), SIZE);
            halls.push_back(hall);
        }
    }
    else if (w > 0)
    {
        if (h < 0)
        {
            if ((0.1 * (rand() % 11)) < 0.5)
            {
                hall.setPosition(point1.first, point2.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point1.first, point2.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
            else
            {
                hall.setPosition(point1.first + SIZE, point1.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point2.first, point2.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
        }
        else if (h > 0)
        {
            if ((0.1 * (rand() % 11)) < 0.5)
            {
                hall.setPosition(point1.first, point1.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point2.first, point1.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
            else
            {
                hall.setPosition(point1.first, point2.second);
                hall.setSize(abs(w), SIZE);
                halls.push_back(hall);
                hall.setPosition(point1.first, point1.second);
                hall.setSize(SIZE, abs(h));
                halls.push_back(hall);
            }
        }
        else // если (h == 0)
        {
            hall.setPosition(point1.first, point1.second);
            hall.setSize(abs(w), SIZE);
            halls.push_back(hall);
        }
    }
    else // если (w == 0)
    {
        if (h < 0)
        {
            hall.setPosition(point2.first, point2.second);
            hall.setSize(SIZE, abs(h));
            halls.push_back(hall);
        }
        else if (h > 0)
        {
            hall.setPosition(point1.first, point1.second);
            hall.setSize(SIZE, abs(h));
            halls.push_back(hall);
        }
    }
}

void Map::create_Map(int width, int height)
{
    Leaf a(0, 0, width, height);
    leafs.push_back(a);
    bool did_split = true;
    while (did_split)
    {
        did_split = false;
        for (int i = 0; i < leafs.size(); ++i)
        {
            if ((!leafs[i].leftChild && !leafs[i].rightChild))
            {
                if (leafs[i].getSize().x > leafs[i].get_MAX_LEAF_SIZE() || leafs[i].getSize().y > leafs[i].get_MAX_LEAF_SIZE() || (0, 1 * rand() % 11) > 0.25)
                {
                    if (leafs[i].Split_into_leaves())
                    {
                        if ((((*leafs[i].leftChild).getPosition().x != 0) && (*leafs[i].leftChild).getPosition().y != 0) || ((*leafs[i].leftChild).getSize().x != 0 && (*leafs[i].leftChild).getSize().y != 0)) {
                            leafs.push_back(*(leafs[i].leftChild));
                        }
                        if (((*leafs[i].rightChild).getPosition().x != 0 && (*leafs[i].rightChild).getPosition().y != 0) || ((*leafs[i].rightChild).getSize().x != 0 && (*leafs[i].rightChild).getSize().y != 0)) {
                            leafs.push_back(*(leafs[i].rightChild));
                        }
                        did_split = true;
                    }
                }
            }
        }
    }
    //Создание комнат
    for (auto& i : leafs) {
        i.CreateRoom();
        if ((!i.room.getPosition().x && !i.room.getPosition().y) || (!i.room.getSize().x && !i.room.getSize().y))continue;
        Rooms.push_back(i.room);
    }
    //Создание коридоров
    for (int i = 0; i < Rooms.size() - 1; ++i) {
        create_halls(Rooms[i], Rooms[i + 1]);
    }
    for (auto& i : halls) {
        allObjectsOnTheMap.push_back(i);
    }
    for (auto& i : Rooms) {
        allObjectsOnTheMap.push_back(i);
    }
}

void Map::createWalls()
{
    //sf::RectangleShape texture_map(sf::Vector2f(75, 75));
    //texture_map.setTexture(&texture_for_map);
    //texture_map.setTextureRect(sf::IntRect(0, 0, 64, 64));
    //for (int i = 0; i < 2160; i += 75) {
    //    for (int j = 0; j < 1400; j += 75) {
    //        texture_map.setPosition(i, j);
    //        map_with_textures.push_back(texture_map);
    //    }
    //}
    GameObject wall;
    wall.setSize(30, 30);
    bool flag = true;
    for (int i = 0; i < width + 50; i += 30) {
        for (int j = 0; j < height + 50; j += 30) {
            for (const auto& obj : allObjectsOnTheMap) {
                if (wall.getGlobalBounds().intersects(obj.getGlobalBounds())) {
                    flag = true;
                }
            }
            if (!flag) {
                Walls.push_back(wall);
            }
            wall.setPosition(i, j);
            flag = false;
        }
    }
}

void Map::createTextures()
{
    sf::Sprite spriteMap;
    textureRoom.loadFromFile("image/Room.png");
    spriteMap.setTexture(textureRoom);

    for (int i = 0; i < width; i += 60) {
        for (int j = 0; j < height; j += 60) {
            spriteMap.setPosition(i, j);
            mapWithTextures.push_back(spriteMap);
        }
    }
    sf::Sprite spriteWalls;
    textureWalls.loadFromFile("image/Walls.png");
    spriteWalls.setTexture(textureWalls);
    for (auto& i : Walls) {
        spriteWalls.setPosition(i.getPosition());
        mapWithTextures.push_back(spriteWalls);
    }
}

sf::Vector2f Map::getRandomCenterRooms() const
{
    sf::Vector2f center;
    int k = randomIntforMap(0, Rooms.size() - 1);
    center.x = Rooms[k].getPosition().x + (Rooms[k].getSize().x) / 2;
    center.y = Rooms[k].getPosition().y + (Rooms[k].getSize().y) / 2;
    return center;
}

void Map::draw(sf::RenderWindow& window)
{
    for (auto& i : mapWithTextures) {
        window.draw(i);
    }
}

