#include "MazeGenerator.h"
#include <vector>

class Maze
{
public:
	std::vector<std::vector<char>> generate(int difficulty);
	static void print(const std::vector<std::vector<char>> maze);
};
