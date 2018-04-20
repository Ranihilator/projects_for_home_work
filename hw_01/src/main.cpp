/*!
\file
\brief application print version and build number
*/

#include <iostream>
#include "version_library.h"

using namespace HW_01;

/*!
\brief Start program

\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char* argv[])
{
	std::cout << "Hello world!" << std::endl;
    version();

	return 0;
}

