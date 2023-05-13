#pragma once
#include <SFML/Graphics.hpp>
class UserInfo
{
public:
	std::string nick;
	int countWin;
	int countGame;
	std::string time;
	int countDeaths;
	UserInfo() {};
	UserInfo(std::string nick, int countWin, int countGame, int countDeaths, std::string time);
};

