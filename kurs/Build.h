#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Statistics.h">
#include "Form.h"
#include "allObjectsInTheGame.h"

class Build
{
private:
	sf::RenderWindow* window;
	bool game(float& timeS, UserInfo& data, Player& hero);
	void level(float& timeS, UserInfo& data, Player& hero);
	int difficulty;
	int lv = 0;
	Form form;
	Statistics statisticsView;
public:
	Build(Form form, Statistics statistics, sf::RenderWindow& window) :window(&window), form(form), statisticsView(statistics), difficulty(1) {};
	UserInfo dataPlayer(std::string nick);
	int menu();
	int login();
	int settings();
	int statistics();
	int endGame(bool typeEnd);
};


