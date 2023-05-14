#pragma once
#include <SFML/Graphics.hpp>
#include "Form.h"
#include "Statistics.h">

class Build
{
private:
	sf::RenderWindow* window;
	bool GAME(float& timeS, UserInfo& data);
	void level(float& timeS, UserInfo& data);
	int difficulty;

	Form form;
	Statistics statisticsView;
public:
	Build(Form form, Statistics statistics, sf::RenderWindow& window) :window(&window), form(form), statisticsView(statistics), difficulty(1) {};
	UserInfo game(std::string nick);
	int menu();
	int login();
	int settings();
	int statistics();
};

