#include "UserInfo.h"

UserInfo::UserInfo(std::string nick, int countWin, int countGame, int countDeaths, std::string time) {
	this->nick = nick;
	this->countWin = countWin;
	this->countGame = countGame;
	this->time = time;
	this->countDeaths = countDeaths;
}