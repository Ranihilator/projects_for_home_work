/*! \file
    \brief Test for matrix N dimension

    \see matrix()
*/

#define BOOST_TEST_MODULE matrix_test

#include <boost/test/unit_test.hpp>

#include "matrix.hpp"
#include <set>

BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_06;

BOOST_AUTO_TEST_CASE(matrix_main)
{
	Matrix <int, -1> matrix;

	BOOST_CHECK(matrix.size() == 0);
	BOOST_CHECK(matrix[0][0] == -1);

	matrix[100][100] = 314;

	BOOST_CHECK(matrix.size() == 1);
	BOOST_CHECK(matrix[0][0] == -1);
	BOOST_CHECK(matrix[0][100] == -1);
	BOOST_CHECK(matrix[100][0] == -1);
	BOOST_CHECK(matrix[100][100] == 314);

	matrix.clear();

	BOOST_CHECK(matrix.size() == 0);
	BOOST_CHECK(matrix[0][0] == -1);
	BOOST_CHECK(matrix[0][0] == -1);
	BOOST_CHECK(matrix[0][100] == -1);
	BOOST_CHECK(matrix[100][0] == -1);
	BOOST_CHECK(matrix[100][100] == -1);

	matrix[100][100] = 217;
	BOOST_CHECK(matrix.size() == 1);
	BOOST_CHECK(matrix[100][100] == 217);

	matrix.clear();
	BOOST_CHECK(matrix.size() == 0);
	BOOST_CHECK(matrix[100][100] == -1);
}

BOOST_AUTO_TEST_CASE(matrix_3x_dimension)
{
	Matrix <int, -1, 3> matrix;

	BOOST_CHECK(matrix.size() == 0);
	BOOST_CHECK(matrix[0][0][0] == -1);

	matrix[100][100][100] = 314;

	BOOST_CHECK(matrix.size() == 1);
	BOOST_CHECK(matrix[0][0][0] == -1);
	BOOST_CHECK(matrix[0][100][0] == -1);
	BOOST_CHECK(matrix[100][0][0] == -1);
	BOOST_CHECK(matrix[100][100][100] == 314);

	matrix.clear();

	BOOST_CHECK(matrix.size() == 0);
	BOOST_CHECK(matrix[0][0][0] == -1);
	BOOST_CHECK(matrix[0][0][0] == -1);
	BOOST_CHECK(matrix[0][100][00] == -1);
	BOOST_CHECK(matrix[100][0][100] == -1);
	BOOST_CHECK(matrix[100][100][100] == -1);

	matrix[100][100][100] = 217;
	BOOST_CHECK(matrix.size() == 1);
	BOOST_CHECK(matrix[100][100][100] == 217);

	matrix.clear();
	BOOST_CHECK(matrix.size() == 0);
	BOOST_CHECK(matrix[100][100][100] == -1);
}

BOOST_AUTO_TEST_CASE(matrix_task)
{
	Matrix <int, -1> matrix;

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

	BOOST_CHECK(matrix.size() == 20);

	for (auto i = 0; i <= 9; ++i)
	{
		BOOST_CHECK(matrix[i][i] == i);
	}
	for (auto i = 10; i <= 100; ++i)
	{
		BOOST_CHECK(matrix[i][i] == -1);
	}
	for (auto i = 0; i <= 9; ++i)
	{
		BOOST_CHECK(matrix[i][9-i] == 9-i);
	}
	for (auto i = 10; i <= 100; ++i)
	{
		BOOST_CHECK(matrix[i][100-i] == -1);
	}

	matrix.clear();

	matrix[0][0] = -1;
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
	matrix[9][0] = -1;

	BOOST_CHECK(matrix.size() == 18);

	matrix.clear();
	BOOST_CHECK(matrix.size() == 0);
}

BOOST_AUTO_TEST_CASE(matrix_iterator)
{
	Matrix <int, -1> matrix;
	std::set<int> result;
	std::set<int> result_model = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

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

	for (auto i : matrix)
	{
		result.insert(std::get<2>(i));
	}

	BOOST_CHECK(result == result_model);
}

BOOST_AUTO_TEST_SUITE_END()
