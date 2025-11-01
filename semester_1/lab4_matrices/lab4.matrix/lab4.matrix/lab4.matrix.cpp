﻿//задание 5; все функции написаны для квадратной матрицы

#include<iostream>
#include<random>
#include <iomanip>
void print_matrix(int** matrix, int num_line)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_line; ++j)
		{
			std::cout << std::setw(4) << matrix[i][j];
		}
		std::cout << "\n";
	}
}
int** din_memory_matrix(int num_line)
{
	int** matrix = new int* [num_line];
	for (int i = 0; i < num_line; ++i)
	{
		matrix[i] = new int[num_line];
	}
	return matrix;
}
void cin_input_matrix(int** matrix, int num_line)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		std::cout << "enter " << i + 1 << " line of matrix: \n";
		for (int j = 0; j < num_line; ++j)
		{
			std::cin >> matrix[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "original matrix: ";
	print_matrix(matrix, num_line);
}
void delete_matrix(int** matrix, int num_line)
{
	for (int i = 0; i < num_line; ++i)
		delete[] matrix[i];
	delete[] matrix;
}
void check_letter()
{
	if (!(std::cin))
	{
		throw "Error! This is not a number\n";
	}
}
void check_negotiv(int value)
{
	if (value <= 0)
	{
		throw "Error! This is a negative number!\n";
	}
}
void enter_num_line(int& num_line)
{
	std::cout << "Enter number of lines: ";
	std::cin >> num_line;
	check_letter();
	check_negotiv(num_line);
}
void input_matrix_choice(int** matrix, int num_line, std::mt19937& gen) {
	int ran_or_not;
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	check_letter();
	switch (ran_or_not) {
	case 0: {
		for (int i = 0; i < num_line; ++i) {
			std::cout << "enter " << i + 1 << " line of matrix: \n";
			for (int j = 0; j < num_line; ++j) {
				std::cin >> matrix[i][j];
				check_letter();
			}
			std::cout << "\n";
		}
		std::cout << "original matrix: ";
		print_matrix(matrix, num_line);
		break;
	}
	case 1: {
		int lower_lim;
		std::cout << "enter the lower limit: ";
		std::cin >> lower_lim;
		check_letter();
		int upper_lim;
		std::cout << "enter the upper limit: ";
		std::cin >> upper_lim;
		check_letter();
		if (lower_lim > upper_lim) {
			std::swap(lower_lim, upper_lim);
		}
		std::uniform_int_distribution<int> dist(lower_lim, upper_lim);
		for (int i = 0; i < num_line; ++i) {
			for (int j = 0; j < num_line; ++j) {
				matrix[i][j] = dist(gen);
			}
		}
		print_matrix(matrix, num_line);
		break;
	}
	default:
		throw "Error, only 1 or 0!\n";
	}
}
int main()
{
	int num_line = 0;
	try {
		enter_num_line(num_line);
		int** matrix = din_memory_matrix(num_line);
		std::mt19937 gen(45218965);
		try {
			input_matrix_choice(matrix, num_line, gen);
			//поиск максимального элемента в правом нижнем треугольнике (с диагональю) матрицы
			int max_triangle_el = matrix[0][num_line - 1];
			int i_max_el = 0, j_max_el = 0; //для следующего задания
			for (int i = 1; i < num_line; ++i)
			{
				for (int j = num_line - 2; j >= num_line - i - 1; --j)
				{
					if (matrix[i][j] > max_triangle_el)
					{
						max_triangle_el = matrix[i][j];
						i_max_el = i, j_max_el = j; //для следующего задания
					}
				}
			}
			std::cout << "the maximum element of the lower right triangle of the matrix = " << max_triangle_el;
			//поиск максимального элеманта в матрице (используем max_triangle_el для этого и идём по оставшимся элементам)
			int max_el = max_triangle_el;
			for (int i = 0; i < num_line- 1 ; ++i)
			{
				for (int j = 0; j < num_line - i; ++j)
				{
					if (matrix[i][j] > max_el)
					{
						max_el = matrix[i][j];
						i_max_el = i, j_max_el = j;
					}
				}
			}
			if (max_el > 0)
			{
				std::cout << "\nMax positiv element in matrix: " << max_el << " in position: " << i_max_el + 1 << ", " << j_max_el + 1;
				for (int j = 0; j < num_line; ++j)
				{
					std::swap(matrix[0][j], matrix[i_max_el][j]);
				}
				for (int i = 0; i < num_line; ++i)
				{
					std::swap(matrix[i][0], matrix[i][j_max_el]);
				}
				std::cout << "\nnew matrix: \n";
				print_matrix(matrix, num_line);
			}
			else
			{
				throw "\nError: There are no positive elements in the array.";
			}
			delete_matrix(matrix, num_line);
		}
		catch (const char* msg) {
			std::cout << msg;
			delete_matrix(matrix, num_line);
			return 1;
		}
	}
	catch (const char* msg) {
		std::cout << msg;
	}
	return 0;
}