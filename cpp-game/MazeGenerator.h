#pragma once

#include <iostream>
#include <vector>

class MazeGenerator
{
public:
	std::vector<std::vector<char>> generateBase(int difficulty);
};