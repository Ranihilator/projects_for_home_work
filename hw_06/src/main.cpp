/*!
\file
\brief Create 2x - dimension sparse matrix

Create 2x matrix
Matrix have sparse elements
Matrix can return size
Matrix can iterrate all node
Matrix can return default value from sparse space
*/

#include "version_library.h"
#include "matrix.hpp"
#include <assert.h>

using namespace HW_06;

#include <iostream>

#define sparse_digit 0

/*!
\brief Start program

\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		if (std::string(argv[1]) == "-v")
			HW_01::version();
		else
		{
			std::cout << "Usage:" << std::endl;
			std::cout << "	matrix without arguments to run" << std::endl;
			std::cout << "	matrix -v Current version print" << std::endl;
			std::cout << std::endl;
		}
		return 0;
	}

	Matrix <int, sparse_digit> matrix;
	assert(matrix.size() == 0);

	auto a = matrix[0][0];
	assert(a == sparse_digit);
	assert(matrix.size() == 0);

	matrix[100][100] = 314;
	assert(matrix[100][100] == 314);
	assert(matrix.size() == 1);

	for(auto c: matrix)
	{
		int x;
		int y;
		int v;

		std::tie(x, y, v) = c;
		std::cout << x << y << v << std::endl;
	}

	matrix.clear();

	matrix[0][0] = 0;
	matrix[1][1] = 1;
	matrix[2][2] = 2;
	matrix[3][3] = 3;
	matrix[4][4] = 4;
	matrix[5][5] = 5;
	matrix[6][6] = 6;
	matrix[7][7] = 7;
	matrix[8][8] = 8;
	matrix[9][9] = 9;

	matrix[0][9] = 9;
	matrix[1][8] = 8;
	matrix[2][7] = 7;
	matrix[3][6] = 6;
	matrix[4][5] = 5;
	matrix[5][4] = 4;
	matrix[6][3] = 3;
	matrix[7][2] = 2;
	matrix[8][1] = 1;
	matrix[9][0] = 0;

	std::cout << "matrix size:" << matrix.size() << std::endl;
	for (auto j = 0; j <= 9; ++j)
	{
		for (auto i = 0; i <= 9; ++i)
		{
			std::cout << matrix[j][i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "matrix size:" << matrix.size() << std::endl;
	for (auto j = 1; j < 9; ++j)
	{
		for (auto i = 1; i < 9; ++i)
		{
			std::cout << matrix[j][i] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "matrix size:" << matrix.size() << std::endl;

	return 0;
}
