#pragma once
#include "SFML/Graphics.hpp"
#include "UserInfo.h"

class Statistics
{
public:
	Statistics();
	void draw(sf::RenderWindow& window);

	void setInfo(std::string nick, int countWin, int countGame, int countDeaths, std::string time);

	std::vector<UserInfo> userInfo;
};