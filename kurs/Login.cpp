#include "Login.h"
#include <ctime>

Login::Login(float width, float height)
{
	login[0].setSize(sf::Vector2f(320, 80));
	login[0].setPosition(sf::Vector2f(width / 2 - 140, height / (MAX_ITEMS + 1) * 1));
	login[0].setFillColor(sf::Color::Transparent);
	login[0].setOutlineColor(sf::Color::White);
	login[0].setOutlineThickness(5);

	login[1].setSize(sf::Vector2f(320, 80));
	login[1].setPosition(sf::Vector2f(width / 2 - 140, height / (MAX_ITEMS + 1) * 2));
	login[1].setFillColor(sf::Color::Transparent);
	login[1].setOutlineColor(sf::Color::White);
	login[1].setOutlineThickness(5);
}

int Login::checkPressed(double x, double y) {
	if (login[0].getGlobalBounds().contains(x, y)) {
		return 1;
	}
	else if (login[1].getGlobalBounds().contains(x, y)) {
		return 2;
	}
	else { return 0; }
}
void Login::draw(sf::RenderWindow& window, std::string nick) {
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

	text.setString("Enter your name \n      in English");
	text.setPosition(login[0].getPosition().x, login[0].getPosition().y - 120);
	window.draw(text);

	text.setString("GO!");
	text.setPosition(login[1].getPosition().x + 110, login[1].getPosition().y + 13);
	window.draw(text);

	window.draw(login[0]);
	sf::Mouse mouse;
	if (login[1].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		window.draw(login[1]);
	}

	sf::Text nickname;
	nickname.setFont(font);
	nickname.setCharacterSize(24);
	nickname.setStyle(sf::Text::Bold);
	nickname.setString(nick);
	nickname.setFillColor(sf::Color::White);
	nickname.setPosition(login[0].getPosition().x + 25, login[0].getPosition().y + 27);
	window.draw(nickname);

	sf::RectangleShape forEnter;
	forEnter.setSize(sf::Vector2f(5, 12));
	forEnter.setPosition(sf::Vector2f(nickname.getLocalBounds().width + nickname.getPosition().x + 12, nickname.getPosition().y + 12));
	forEnter.setFillColor(sf::Color::White);
	forEnter.setOutlineThickness(5);

	std::time_t tim = time(0);

	if (tim % 2) {
		window.draw(forEnter);
	}
}
