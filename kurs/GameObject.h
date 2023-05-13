#pragma once
#include <string>
#include "SFML/Graphics.hpp"
//Класс прямоугольник
class GameObject
{
protected:
	int x, y;
	int width, height;
	std::string path = "";
	sf::Texture texture;
	sf::Sprite sprite;
public:
	sf::Sprite getSprite()const { return sprite; }
	sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }
	sf::Vector2f getSize() const { return sf::Vector2f(width, height); }

	GameObject() :x(0), y(0), width(0), height(0) {}
	GameObject(int x, int y, int width, int height) :x(x), y(y), width(width), height(height) {}
	GameObject(sf::Vector2f position, sf::Vector2f size) :x(position.x), y(position.y), width(size.x), height(size.y) {}

	sf::FloatRect getGlobalBounds() const { return sf::FloatRect(sf::Vector2f(x, y), sf::Vector2f(width, height)); }

	void setSpriteLoadFromFile(std::string path_texture) {
		path = path_texture;
		texture.loadFromFile(path);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, width, height));
		sprite.setPosition(x, y);
	}
	void setColor(uint8_t red, uint8_t green, uint8_t blue) {
		sprite.setColor(sf::Color(red, green, blue));
	}
	void setPosition(int x, int y) {
		this->x = x;
		this->y = y;
		sprite.setPosition(x, y);
	}
	void setSize(int width, int height) {
		this->width = width;
		this->height = height;
	}

	virtual ~GameObject() {}
};

