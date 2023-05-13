#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
	menu[0].setSize(sf::Vector2f(320, 80));
	menu[0].setPosition(sf::Vector2f(width / 2 - 140, height / (MAX_ITEMS + 1) * 1));
	menu[0].setFillColor(sf::Color::Transparent);
	menu[0].setOutlineThickness(5);
	menu[0].setOutlineColor(sf::Color::White);

	menu[1].setSize(sf::Vector2f(320, 80));
	menu[1].setPosition(sf::Vector2f(width / 2 - 140, height / (MAX_ITEMS + 1) * 2));
	menu[1].setFillColor(sf::Color::Transparent);
	menu[1].setOutlineThickness(5);
	menu[1].setOutlineColor(sf::Color::White);
}

int Menu::checkPressed(double x, double y) {
	if (menu[0].getGlobalBounds().contains(x, y)) {
		return 1;
	}
	else if (menu[1].getGlobalBounds().contains(x, y)) {
		return 2;
	}
}

void Menu::draw(sf::RenderWindow& window) {
	window.clear();

	sf::Texture texture;
	texture.loadFromFile("image/fon_menu.jpg");
	sf::Sprite sprite;
	sf::Vector2f targetSize(window.getSize().x * 1.43, window.getSize().y * 1.55);
	sprite.setTexture(texture);
	sprite.setScale(targetSize.x / sprite.getLocalBounds().width, targetSize.y / sprite.getLocalBounds().height);
	sprite.setPosition(-820, -500);
	window.draw(sprite);

	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);

	text.setString("Start");
	text.setPosition(menu[0].getPosition().x + 110, menu[0].getPosition().y + 13);
	window.draw(text);

	text.setString("Statistics");
	text.setPosition(menu[1].getPosition().x + 70, menu[1].getPosition().y + 13);
	window.draw(text);

	sf::Mouse mouse;

	if (menu[0].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		window.draw(menu[0]);
	}
	if (menu[1].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		window.draw(menu[1]);
	}
}
