#include "MazeGenerator.h"
#include <random>
#include <iostream>

class Maze
{
public:
	MazeGenerator a;
	std::shared_ptr<std::vector<std::vector<char>>> generate(unsigned width, unsigned height)
	{
		std::shared_ptr<std::vector<std::vector<char>>> maze = a.generate(20, 20);

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> ran(1, maze->size()*maze->size());

		for (int i = 3; i < maze->size()-3; i++) {
			for (int j = 3; j < maze->size()-3; j++) {
				if (ran(rng) == 1 || ran(rng) == 2 || ran(rng) == 3 ||
					ran(rng) == 4 || ran(rng) == 5 || ran(rng) == 6 || 
					ran(rng) == 7 || ran(rng) == 8 || ran(rng) == 9) {

					maze.get()->at(i).at(j) = '#';
					maze.get()->at(i + 1).at(j) = '#';
					maze.get()->at(i - 1).at(j) = '#';
					maze.get()->at(i + 2).at(j) = '#';
					maze.get()->at(i - 2).at(j) = '#';

					maze.get()->at(i).at(j - 1) = '#';
					maze.get()->at(i + 1).at(j - 1) = '#';
					maze.get()->at(i - 1).at(j - 1) = '#';
					maze.get()->at(i + 2).at(j - 1) = '#';
					maze.get()->at(i - 2).at(j - 1) = '#';

					maze.get()->at(i).at(j - 2) = '#';
					maze.get()->at(i + 1).at(j - 2) = '#';
					maze.get()->at(i - 1).at(j - 2) = '#';
					maze.get()->at(i + 2).at(j - 2) = '#';
					maze.get()->at(i - 2).at(j - 2) = '#';

					maze.get()->at(i).at(j + 1) = '#';
					maze.get()->at(i + 1).at(j + 1) = '#';
					maze.get()->at(i - 1).at(j + 1) = '#';
					maze.get()->at(i + 2).at(j + 1) = '#';
					maze.get()->at(i - 2).at(j + 1) = '#';

					maze.get()->at(i).at(j + 2) = '#';
					maze.get()->at(i + 1).at(j + 2) = '#';
					maze.get()->at(i - 1).at(j + 2) = '#';
					maze.get()->at(i + 2).at(j + 2) = '#';
					maze.get()->at(i - 2).at(j + 2) = '#';
				}
			}
		}
		return maze;
	}
	static void print(const std::shared_ptr<std::vector<std::vector<char>>>& maze)
	{
		// Проверяем указатель на nullptr
		if (maze == nullptr)
			return;

		// Построчно считываем и выводим в консоль
		for (unsigned i = 0; i < maze.get()->size(); ++i)
		{
			for (unsigned j = 0; j < maze.get()->at(0).size(); ++j)
				std::cout << maze.get()->at(i).at(j);
			std::cout << std::endl;
		}
	}
};
