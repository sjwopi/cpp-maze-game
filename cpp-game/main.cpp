#include "Maze.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int ts = 80;
float OffsetX = 0;
float OffsetY = 0;

int main() {
	Maze maze1;
	// в generate передаем сложность
	// 1 - легко
	// 2 - нормально
	// 3 - сложно
	// 4 - экстрим
	std::vector<std::vector<char>> mainGame = maze1.generate(3);
	maze1.print(mainGame);
	
	sf::RenderWindow window(sf::VideoMode(1040, 1040), "Maze");

	sf::RectangleShape wall(sf::Vector2f(ts, ts));

	sf::RectangleShape user(sf::Vector2f(ts, ts));

	user.setPosition(ts, ts);
	user.setFillColor(sf::Color::Blue);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Right) {
					OffsetX += ts;
					//if (OffsetX <= ts * 6) {
					//	if (OffsetY <= ts * 6)
					//		user.setPosition(OffsetX, OffsetY);
					//	else
					//		user.setPosition(OffsetX, ts * 6);
					//
					//	OffsetX = 0;
					//}
					//else
					//	OffsetX += ts;
				}
				if (event.key.code == sf::Keyboard::Left) {
					OffsetX -= ts;
				}
				if (event.key.code == sf::Keyboard::Up) {
					OffsetY -= ts;
				}
				if (event.key.code == sf::Keyboard::Down) {
					OffsetY += ts;
				}
			}
		}


		if (OffsetX < 0)
			OffsetX = 0;
		else if (OffsetX > ts * (mainGame.size() - 4))
			OffsetX = ts * (mainGame.size() - 4);

		if (OffsetY < 0)
			OffsetY = 0;
		else if ((OffsetY > ts * (mainGame.size() - 3)) && OffsetX == ts * (mainGame.size() - 4)) {
			std::cout << 'a';
			OffsetY = ts * (mainGame.size() - 3);
		}

		else if ((OffsetY > ts * (mainGame.size() - 4)) && OffsetX != ts * (mainGame.size() - 4))
			OffsetY = ts * (mainGame.size() - 4);

		window.clear(sf::Color::White);
		for (int i = 0; i < mainGame.size()-1; i++)
			for (int j = 0; j < mainGame.size()-1; j++) {

				if (mainGame[i][j] == '#')
				{
					wall.setPosition(j * ts - OffsetX, i * ts - OffsetY);
					wall.setFillColor(sf::Color::Black);
				}
				else if (mainGame[i][j] == '-')
				{
					wall.setPosition(j * ts - OffsetX, i * ts - OffsetY);
					wall.setFillColor(sf::Color::Green);
				}
				else if (mainGame[i][j] == '@')
				{
					wall.setPosition(j * ts - OffsetX, i * ts - OffsetY);
					wall.setFillColor(sf::Color::Red);
				}

				window.draw(wall);
			}

		window.draw(user);
		window.display();
	}


	return 0;
}