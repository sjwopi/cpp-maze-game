#include "MazeGenerator.h"
#include "Maze.h"
#include <iostream>
#include <vector>
#include <random>

std::vector<std::vector<char>> Maze::generate(int difficulty)
{
	MazeGenerator a;
	std::vector<std::vector<char>> maze = a.generateBase(difficulty);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> ran(1, maze.size()*maze.size());

	//–андомна€ генераци€ комнат
	for (int i = 4; i < maze.size() - 4; i++) {
		for (int j = 4; j < maze.size() - 4; j++) {
			if (ran(rng) == 1 || ran(rng) == 2 || ran(rng) == 3
				//|| ran(rng) == 4 || ran(rng) == 5 || ran(rng) == 6
				//|| ran(rng) == 7 || ran(rng) == 8 || ran(rng) == 9
				) {

				maze[i][j] = '@';
				maze[i + 1][j] = '-';
				maze[i - 1][j] = '-';
				maze[i + 2][j] = '-';
				maze[i - 2][j] = '-';

				maze[i][j - 1] = '-';
				maze[i + 1][j - 1] = '-';
				maze[i - 1][j - 1] = '-';
				maze[i + 2][j - 1] = '-';
				maze[i - 2][j - 1] = '-';

				maze[i][j - 2] = '-';
				maze[i + 1][j - 2] = '-';
				maze[i - 1][j - 2] = '-';
				maze[i + 2][j - 2] = '-';
				maze[i - 2][j - 2] = '-';

				maze[i][j + 1] = '-';
				maze[i + 1][j + 1] = '-';
				maze[i - 1][j + 1] = '-';
				maze[i + 2][j + 1] = '-';
				maze[i - 2][j + 1] = '-';

				maze[i][j + 2] = '-';
				maze[i + 1][j + 2] = '-';
				maze[i - 1][j + 2] = '-';
				maze[i + 2][j + 2] = '-';
				maze[i - 2][j + 2] = '-';
			}
		}
	}

	//генераци€ комнаты с боссом
	maze[maze.size() - 5][maze.size() - 5] = '@';
	maze[maze.size() - 5 + 1][maze.size() - 5] = '-';
	maze[maze.size() - 5 - 1][maze.size() - 5] = '-';
	maze[maze.size() - 5 + 2][maze.size() - 5] = '-';
	maze[maze.size() - 5 - 2][maze.size() - 5] = '-';

	maze[maze.size() - 5][maze.size() - 5 - 1] = '-';
	maze[maze.size() - 5 + 1][maze.size() - 5 - 1] = '-';
	maze[maze.size() - 5 - 1][maze.size() - 5 - 1] = '-';
	maze[maze.size() - 5 + 2][maze.size() - 5 - 1] = '-';
	maze[maze.size() - 5 - 2][maze.size() - 5 - 1] = '-';

	maze[maze.size() - 5][maze.size() - 5 - 2] = '-';
	maze[maze.size() - 5 + 1][maze.size() - 5 - 2] = '-';
	maze[maze.size() - 5 - 1][maze.size() - 5 - 2] = '-';
	maze[maze.size() - 5 + 2][maze.size() - 5 - 2] = '-';
	maze[maze.size() - 5 - 2][maze.size() - 5 - 2] = '-';

	maze[maze.size() - 5][maze.size() - 5 + 1] = '-';
	maze[maze.size() - 5 + 1][maze.size() - 5 + 1] = '-';
	maze[maze.size() - 5 - 1][maze.size() - 5 + 1] = '-';
	maze[maze.size() - 5 + 2][maze.size() - 5 + 1] = '-';
	maze[maze.size() - 5 - 2][maze.size() - 5 + 1] = '-';

	maze[maze.size() - 5][maze.size() - 5 + 2] = '-';
	maze[maze.size() - 5 + 1][maze.size() - 5 + 2] = '-';
	maze[maze.size() - 5 - 1][maze.size() - 5 + 2] = '-';
	maze[maze.size() - 5 + 2][maze.size() - 5 + 2] = '-';
	maze[maze.size() - 5 - 2][maze.size() - 5 + 2] = '-';

	for (int i = 0; i < maze.size(); i++) {
		maze[i][maze.size() - 2] = '#';
		maze[maze.size() - 2][i] = '#';
	}
	maze[maze.size() - 2][maze.size() - 3] = '$';

	return maze;
}
void Maze::print(const std::vector<std::vector<char>> maze)
{
	// ѕострочно считываем и выводим в консоль
	for (unsigned i = 0; i < maze.size() - 1; ++i)
	{
		for (unsigned j = 0; j < maze.size() - 1; ++j)
			std::cout << maze[i][j];
		std::cout << std::endl;
	}
}