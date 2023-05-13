#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Login.h"
#include "Statistics.h">

class Build
{
private:
	sf::RenderWindow* window;
	bool GAME(float& timeS, UserInfo& data);
	void level(float& timeS, UserInfo& data);
public:
	Build(sf::RenderWindow& window) :window(&window) {};
	UserInfo game(sf::RenderWindow& window, Menu menu, Login login, Statistics statistics, std::string nick);
	int menu(/*sf::RenderWindow& window, */Menu menu, Login login, Statistics statistics);
	int login(sf::RenderWindow& window, Menu menu, Login login, Statistics statistics);
	int statistics(sf::RenderWindow& window, Menu menu, Login login, Statistics statistics);
};

