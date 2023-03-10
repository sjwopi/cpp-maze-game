#include "Maze.h"

int main() {
	Maze mainGame;
	// в generate передаем сложность
	// 1 - легко
	// 2 - нормально
	// 3 - сложно
	// 4 - экстрим
	mainGame.print(mainGame.generate(2));
	return 0;
}