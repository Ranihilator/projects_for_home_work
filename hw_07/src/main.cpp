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

using namespace HW_07;

#include <iostream>

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

	return 0;
}
