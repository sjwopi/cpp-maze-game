#include "Statistics.h"
#include "UserInfo.h"
#include <iostream>
#include <fstream>

Statistics::Statistics() {
	std::string nick;
	std::string cWin;
	std::string cGame;
	std::string cDeath;
	std::string time;
	std::ifstream in("test.txt");

	while (in >> nick >> cWin >> cGame >> cDeath >> time)
	{
		UserInfo a(nick, std::atoi(cWin.c_str()), std::atoi(cGame.c_str()), std::atoi(cDeath.c_str()), time);
		userInfo.push_back(a);
	}
	in.close();
}
void Statistics::setInfo(std::string nick, int countWin, int countGame, int countDeaths, std::string time) {
	bool flag = true;
	userInfo.clear();

	std::string nickN;
	std::string cWin;
	std::string cGame;
	std::string cDeath;
	std::string timeN;
	std::ifstream in("test.txt");

	while (in >> nickN >> cWin >> cGame >> cDeath >> timeN)
	{
		if (nickN == nick) {
			countWin += atoi(cWin.c_str());
			countGame += atoi(cGame.c_str());
			countDeaths += atoi(cDeath.c_str());

			if (std::stoi(timeN) < std::stoi(time)) {
				timeN = time;
			}
			flag = false;

			UserInfo a(nickN, countWin, countGame, countDeaths, timeN);
			userInfo.push_back(a);
		}
		else {
			UserInfo a(nickN, atoi(cWin.c_str()), atoi(cGame.c_str()), atoi(cDeath.c_str()), timeN);
			userInfo.push_back(a);
		}
	}
	in.close();

	if (flag) {
		UserInfo a(nick, countWin, countGame, countDeaths, time);
		userInfo.push_back(a);
	}

	std::ofstream fout;
	fout.open("test.txt", std::ofstream::out | std::ofstream::trunc);
	for (int i = 0; i < userInfo.size(); i++) {
		fout << userInfo[i].nick << " " << userInfo[i].countWin << " " << userInfo[i].countGame << " " << userInfo[i].countDeaths << " " << userInfo[i].time << std::endl;
	}
	fout.close();
}
void Statistics::draw(sf::RenderWindow& window) {

	sf::Texture texture;
	texture.loadFromFile("image/fon_menu.jpg");
	sf::Sprite sprite;
	sf::Vector2f targetSize(window.getSize().x * 1.43, window.getSize().y * 1.55);
	sprite.setTexture(texture);
	sprite.setScale(targetSize.x / sprite.getLocalBounds().width, targetSize.y / sprite.getLocalBounds().height);
	sprite.setPosition(-820, -500);
	window.draw(sprite);

	sf::RectangleShape line(sf::Vector2f(window.getSize().x - 120, 2));
	line.setFillColor(sf::Color::White);
	line.setPosition(60, 100);
	window.draw(line);

	sf::RectangleShape lineV(sf::Vector2f(window.getSize().y - 100, 2));
	lineV.rotate(90);
	lineV.setPosition(320, 40);
	window.draw(lineV);
	lineV.setPosition(660, 40);
	window.draw(lineV);
	lineV.setPosition(1000, 40);
	window.draw(lineV);
	lineV.setPosition(1380, 40);
	window.draw(lineV);

	sf::Font font;
	font.loadFromFile("font.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(32);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::White);

	text.setString("Username");
	text.setPosition(100, 60);
	window.draw(text);
	text.setString("Number of wins");
	text.setPosition(360, 60);
	window.draw(text);
	text.setString("Number of games");
	text.setPosition(680, 60);
	window.draw(text);
	text.setString("Number of deaths");
	text.setPosition(1037, 60);
	window.draw(text);
	text.setString("Maximum playing time");
	text.setPosition(1410, 60);
	window.draw(text);

	std::string nick;
	std::string cWin;
	std::string cGame;
	std::string cDeath;
	std::string time;
	std::ifstream in("test.txt");
	int i = 0;
	while (in >> nick >> cWin >> cGame >> cDeath >> time)
	{
		text.setString(nick);
		text.setPosition(100, 160 + 100 * i);
		window.draw(text);
		text.setString(cWin);
		text.setPosition(510, 160 + 100 * i);
		window.draw(text);
		text.setString(cGame);
		text.setPosition(830, 160 + 100 * i);
		window.draw(text);
		text.setString(cDeath);
		text.setPosition(1190, 160 + 100 * i);
		window.draw(text);
		text.setString(time + "s");
		text.setPosition(1550, 160 + 100 * i);
		window.draw(text);
		i++;
	}
	in.close();
}