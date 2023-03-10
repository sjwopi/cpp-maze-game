#include "MazeGenerator.h"
#include <iostream>
#include <vector>
#include <memory>
#include <random>

std::shared_ptr<std::vector<std::vector<char>>> MazeGenerator::generate (unsigned width, unsigned height)
{
	// Проверим ограничения параметров на 0
	if ((width < 1) || (height < 1))
		return nullptr;

	const auto top_limit = std::numeric_limits<unsigned>::max();
	// Проверим ограничения по максимальному допустимому размеру
	if (((top_limit - 1) / 2 <= width) || ((top_limit - 1) / 2 <= height))
		return nullptr;

	// Инициализируем размер конечной матрицы maze
	// Ячейки будут представлять из себя фрагменты 2x2 + 1 одно значение сверху и слева для стен
	const unsigned output_height = height * 2 + 1;
	const unsigned output_width = width * 2 + 1;
	// Инициализируем указатель на лабиринт
	auto maze = std::make_shared<std::vector<std::vector<char>>>();
	// Зарезервируем размер лабиринта по высоте
	maze.get()->reserve(output_height);

	for (unsigned i = 0; i < output_height; ++i)
	{
		std::vector<char> row;
		row.reserve(output_width);
		for (unsigned j = 0; j < output_width; ++j)
			// Если этот элемент в строке является ячейкой в левом верхнем угле области 2x2 - то это пустая ячейка в лабиринте
			if ((i % 2 == 1) && (j % 2 == 1))
				row.push_back(' ');
			else
				// Если это область для стены справа или область для стены снизу - то инициализируем этот элемент пустой ячейкой в лабиринте
				if (((i % 2 == 1) && (j % 2 == 0) && (j != 0) && (j != output_width - 1)) ||
					((j % 2 == 1) && (i % 2 == 0) && (i != 0) && (i != output_height - 1)))
				{
					row.push_back(' ');
				}
				else
					// Во всех остальных случаях устанавливаем стену
				{
					row.push_back('*');
				}
		maze.get()->push_back(std::move(row));
	}
	// Создайте первую строку лабиринта.Ниодна ячейка не будет принадлежать какому - либо множеству.
	// Инициализируем вспомогательную строку, которая будет содержать в себе принадлежность ко множеству для ячейки из алгоритма
	std::vector<unsigned> row_set;
	row_set.reserve(width);
	// 0 - будет означать, что ячейка не принадлежит никакому множеству
	for (unsigned i = 0; i < width; ++i)
		row_set.push_back(0);
	// И инициализируем счетчик для множеств
	unsigned set = 1;
	// Инициализируем генератор случайных чисел
	std::random_device rd;
	std::mt19937 mt(rd());
	// от 0 до 2 (2 не входит) и после привидения к int будет либо 0 - где стены нет, либо 1 - стену решили установить
	std::uniform_int_distribution<int> dist(0, 2);

	// Организуем цикл алгоритма Эллера
	for (unsigned i = 0; i < height; ++i)
	{
		// Присвоить каждой ячейке, которая не входит ни в одно множество, своё уникальное множество.
		for (unsigned j = 0; j < width; ++j)
			if (row_set[j] == 0)
				row_set[j] = set++;

		// Создайте правые стены для ячеек, двигаясь слева направо, следующим образом :
		for (unsigned j = 0; j < width - 1; ++j)
		{
			// Случайным образом решите, добавлять стену или нет
			const auto right_wall = dist(mt);
			// Если текущая ячейка и ячейка справа являются членами одного и того же множества, всегда создавайте между ними стену(это предотвратит петли)
			if ((right_wall == 1) || (row_set[j] == row_set[j + 1]))
				maze.get()->at(i * 2 + 1).at(j * 2 + 2) = '*';
			else
			{
				const auto changing_set = row_set[j + 1];
				for (unsigned l = 0; l < width; ++l)
					if (row_set[l] == changing_set)
						row_set[l] = row_set[j];
			}
		}

		// Создайте нижние стены, двигаясь слева направо :
		for (unsigned j = 0; j < width; ++j)
		{
			// Случайным образом решите, добавлять нижнюю стену или нет. 
			const auto bottom_wall = dist(mt);

			unsigned int count_current_set = 0;
			for (unsigned l = 0; l < width; ++l)
				// считаем количество ячеек текущего множества
				if (row_set[j] == row_set[l])
					count_current_set++;

			if ((bottom_wall == 1) && (count_current_set != 1))
				maze.get()->at(i * 2 + 2).at(j * 2 + 1) = '*';
		}

		// продолжать добавлять строки или остановиться и завершить лабиринт

		if (i != height - 1)
		{
			// Убеждаемся, что каждая область имеет по крайней мере одну ячейку без нижней стены(это предотвратит создание изолированных областей)
			for (unsigned j = 0; j < width; ++j) {
				unsigned count_hole = 0;
				for (unsigned l = 0; l < width; ++l)
					if ((row_set[l] == row_set[j]) && (maze.get()->at(i * 2 + 2).at(l * 2 + 1) == ' '))
						count_hole++;
				if (count_hole == 0)
					maze.get()->at(i * 2 + 2).at(j * 2 + 1) = ' ';
			}

			for (unsigned j = 0; j < width; ++j)
				// Проверим надичие нижней стены у текущего ряда
				// Если стенка есть, то удаляем ячейку из множества
				if (maze.get()->at(i * 2 + 2).at(j * 2 + 1) == '*') { row_set[j] = 0; }
		}
	}

	for (unsigned int j = 0; j < width - 1; ++j)
	{
		// Если текущая ячейка и ячейка справа являются членами разных множеств
		if (row_set[j] != row_set[j + 1])
			// то удалить правую стену
			maze.get()->at(output_height - 2).at(j * 2 + 2) = ' ';
	}
	// вернем указатель на полученный лабиринт
	return maze;
}