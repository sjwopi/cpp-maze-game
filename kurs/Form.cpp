#include "Form.h"
#include <iostream>

Form::Form(float width, float height, sf::RenderWindow& window) :window(&window)
{
	btn[0].setSize(sf::Vector2f(320, 80));
	btn[0].setPosition(sf::Vector2f(width / 2 - 140, height * 0.2));
	btn[0].setFillColor(sf::Color::Transparent);
	btn[0].setOutlineThickness(5);
	btn[0].setOutlineColor(sf::Color::White);

	btn[1] = btn[0];
	btn[1].setPosition(sf::Vector2f(width / 2 - 140, height * 0.4));
	btn[2] = btn[0];
	btn[2].setPosition(sf::Vector2f(width / 2 - 140, height * 0.6));

	fonTexture.loadFromFile("image/fon_menu.jpg");

	sf::Vector2f targetSize((*this->window).getSize().x * 1.43, (*this->window).getSize().y * 1.55);
	fon.setTexture(fonTexture);
	fon.setScale(targetSize.x / fon.getLocalBounds().width, targetSize.y / fon.getLocalBounds().height);
	fon.setPosition(-820, -500);

	font.loadFromFile("font.ttf");

	text[0].setFont(font);
	text[0].setCharacterSize(40);
	text[0].setStyle(sf::Text::Bold);
	text[0].setFillColor(sf::Color::White);
	text[1] = text[0];
	text[2] = text[0];
	text[3] = text[0];
}

int Form::checkPressed(double x, double y) {
	if (btn[0].getGlobalBounds().contains(x, y)) {
		return 1;
	}
	else if (btn[1].getGlobalBounds().contains(x, y)) {
		return 2;
	}
	else if (btn[2].getGlobalBounds().contains(x, y)) {
		return 3;
	}
}

void Form::drawLogin(std::string nick) {
	(*window).clear();

	(*window).draw(fon);

	text[0].setString("Enter your name \n      in English");
	text[0].setPosition(btn[0].getPosition().x, btn[0].getPosition().y - 120);
	(*window).draw(text[0]);

	text[1].setString("GO!");
	text[1].setPosition(btn[1].getPosition().x +110, btn[1].getPosition().y + 13);
	(*window).draw(text[1]);

	sf::Text nickname;
	nickname.setFont(font);
	nickname.setCharacterSize(24);
	nickname.setStyle(sf::Text::Bold);
	nickname.setString(nick);
	nickname.setFillColor(sf::Color::White);
	nickname.setPosition(btn[0].getPosition().x + 25, btn[0].getPosition().y + 27);
	(*window).draw(nickname);

	sf::RectangleShape forEnter;
	forEnter.setSize(sf::Vector2f(5, 12));
	forEnter.setPosition(sf::Vector2f(nickname.getLocalBounds().width + nickname.getPosition().x + 12, nickname.getPosition().y + 12));
	forEnter.setFillColor(sf::Color::White);
	forEnter.setOutlineThickness(5);
	std::time_t tim = time(0);
	if (tim % 2) {
		(*window).draw(forEnter);
	}

	sf::Mouse mouse;
	if (btn[0].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[0]);
	}
	if (btn[1].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[1]);
	}

		
}

void Form::drawMenu() {
	(*window).clear();

	(*window).draw(fon);

	text[0].setString("Start");
	text[0].setPosition(btn[0].getPosition().x + 110, btn[0].getPosition().y + 13);
	(*window).draw(text[0]);

	text[1].setString("Statistics");
	text[1].setPosition(btn[1].getPosition().x + 70, btn[1].getPosition().y + 13);
	(*window).draw(text[1]);

	text[2].setString("Settings");
	text[2].setPosition(btn[2].getPosition().x + 80, btn[2].getPosition().y + 13);
	(*window).draw(text[2]);

	sf::Mouse mouse;
	if (btn[0].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[0]);
	}
	else if (btn[1].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[1]);
	}
	else if (btn[2].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[2]);
	}
}

void Form::drawSettings() {
	(*window).clear();

	(*window).draw(fon);

	text[0].setString("Easy");
	text[0].setPosition(btn[0].getPosition().x + 110, btn[0].getPosition().y + 13);
	(*window).draw(text[0]);

	text[1].setString("Normal");
	text[1].setPosition(btn[1].getPosition().x + 80, btn[1].getPosition().y + 13);
	(*window).draw(text[1]);

	text[2].setString("Hard");
	text[2].setPosition(btn[2].getPosition().x + 110, btn[2].getPosition().y + 13);
	(*window).draw(text[2]);

	text[3].setString("Choose the difficulty of the game");
	text[3].setPosition(400, 200);
	(*window).draw(text[3]);

	sf::Mouse mouse;
	if (btn[0].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[0]);
	} else if (btn[1].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[1]);
	} else if (btn[2].getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y)) {
		(*window).draw(btn[2]);
	}
}
