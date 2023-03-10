#pragma once

#include <iostream>
#include <vector>

class MazeGenerator
{
public:
	std::shared_ptr<std::vector<std::vector<char>>> generate(unsigned width, unsigned height);
};