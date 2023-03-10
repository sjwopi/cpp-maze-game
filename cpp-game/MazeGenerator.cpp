#include "MazeGenerator.h"
#include <iostream>
#include <vector>
#include <memory>
#include <random>

std::vector<std::vector<char>> MazeGenerator::generateBase (int difficulty = 1)
{
	int defaultDifficulty = 10 * difficulty;
	// Инициализируем размер конечной матрицы maze
	const int size = defaultDifficulty * 2 + 2;
	std::vector<std::vector<char>> maze = std::vector<std::vector<char>>();
	// Зарезервируем размер лабиринта
	maze.reserve(size);

	for (int i = 0; i < size; ++i)
	{
		std::vector<char> row;
		row.reserve(size);
		for (int j = 0; j < size; ++j)
			if ((i % 2 == 1) && (j % 2 == 1))
				row.push_back(' ');
			else
				if (((i % 2 == 1) && (j % 2 == 0) && (j != 0) && (j != size - 1)) ||
					((j % 2 == 1) && (i % 2 == 0) && (i != 0) && (i != size - 1)))
				{
					row.push_back(' ');
				}
				else
				{
					row.push_back('#');
				}
		maze.push_back(std::move(row));
	}

	// Создаем первую строку лабиринта и присваиваем каждому символу 0
	// 0 - будет означать, что ячейка не принадлежит никакому множеству #1(см. ниже)
	std::vector<int> row_set;
	row_set.reserve(defaultDifficulty);

	for (int i = 0; i < defaultDifficulty; ++i)
		row_set.push_back(0);
	// Инициализируем счетчик для множеств
	int set = 1;
	// Инициализируем генератор случайных чисел (0 - нет стены, 1 - есть стена)
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 2);

	// Организуем цикл алгоритма Эллера
	for (int i = 0; i < defaultDifficulty; ++i)
	{
		// Присвоить каждой ячейке, которая не входит ни в одно множество, своё уникальное множество. #1(см. выше)
		for (int j = 0; j < defaultDifficulty; ++j)
			if (row_set[j] == 0)
				row_set[j] = set++;

		// Создайте правые стены для ячеек, двигаясь слева направо, следующим образом :
		for (int j = 0; j < defaultDifficulty - 1; ++j)
		{
			// Случайным образом решите, добавлять стену или нет
			const auto right_wall = dist(mt);
			// Если текущая ячейка и ячейка справа являются членами одного и того же множества, всегда создавайте между ними стену(это предотвратит петли)
			if ((right_wall == 1) || (row_set[j] == row_set[j + 1]))
				maze[i * 2 + 1][j * 2 + 2] = '#';
			else
			{
				const auto changing_set = row_set[j + 1];
				for (int l = 0; l < defaultDifficulty; ++l)
					if (row_set[l] == changing_set)
						row_set[l] = row_set[j];
			}
		}

		// Создайте нижние стены, двигаясь слева направо :
		for (int j = 0; j < defaultDifficulty; ++j)
		{
			// Случайным образом решите, добавлять нижнюю стену или нет. 
			const auto bottom_wall = dist(mt);

			int count_current_set = 0;
			for (int l = 0; l < defaultDifficulty; ++l)
				// считаем количество ячеек текущего множества
				if (row_set[j] == row_set[l])
					count_current_set++;

			if ((bottom_wall == 1) && (count_current_set != 1))
				maze[i * 2 + 2][j * 2 + 1] = '#';
		}

		// продолжать добавлять строки или остановиться и завершить лабиринт

		if (i < defaultDifficulty)
		{
			// Убеждаемся, что каждая область имеет по крайней мере одну ячейку без нижней стены(это предотвратит создание изолированных областей)
			for (int j = 0; j < defaultDifficulty; ++j) {
				int count_hole = 0;
				for (int l = 0; l < defaultDifficulty; ++l)
					if ((row_set[l] == row_set[j]) && (maze[i * 2 + 2][l * 2 + 1] == ' '))
						count_hole++;
				if (count_hole == 0)
					maze[i * 2 + 2][j * 2 + 1] = ' ';
			}

			for (int j = 0; j < defaultDifficulty; ++j)
				// Проверим надичие нижней стены у текущего ряда
				// Если стенка есть, то удаляем ячейку из множества
				if (maze[i * 2 + 2][j * 2 + 1] == '#') { row_set[j] = 0; }
		}
	}

	for (int j = 0; j < defaultDifficulty - 1; ++j)
	{
		// Если текущая ячейка и ячейка справа являются членами разных множеств
		if (row_set[j] != row_set[j + 1])
			// то удалить правую стену
			maze[size - 2][j * 2 + 2] = ' ';
	}
	// вернем указатель на полученный лабиринт
	return maze;
}
