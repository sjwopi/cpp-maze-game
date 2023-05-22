#pragma once
#include <SFML/Graphics.hpp>
struct UserInfo
{
	std::string nick;
	int countWin;
	int countGame;
	std::string time;
	int countDeaths;
	UserInfo() {};
	UserInfo(std::string nick, int countWin, int countGame, int countDeaths, std::string time);
};

