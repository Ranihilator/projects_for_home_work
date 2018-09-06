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
#include "bulk.hpp"

#include <iostream>

using namespace HW_07;

size_t cmd_1(void* arg)
{
	std::ostringstream *ss = static_cast<std::ostringstream *>(arg);

	if (ss != nullptr)
		*ss << "cmd1";

	return 0;
}

size_t cmd_2(void* arg)
{
	std::ostringstream *ss = static_cast<std::ostringstream *>(arg);

	if (ss != nullptr)
		*ss << "cmd2";

	return 0;
}

/*!
\brief Start program
\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char* argv[])
{
	size_t N = 0;
	if (argc <= 1)
	{
			std::cout << "Usage:" << std::endl;
			std::cout << "run bulk with 1 arguments Int number (size of cmd sequence)" << std::endl;
			std::cout << std::endl;
			return 0;
	}
	else
	{
		N = std::atoll(argv[1]);

		if (N == 0)
			N = 3;
	}

	Bulk bulk
	(N, {
		{"cmd1", cmd_1},
		{"cmd2", cmd_2},
	});

	LOG::Console console(&bulk);
	LOG::File file(&bulk);

	for(std::string line; std::getline(std::cin, line);)
	{
		bulk.Act(line);
	}

	return 0;
}
