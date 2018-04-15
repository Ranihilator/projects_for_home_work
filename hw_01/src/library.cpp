/*!
\file
\brief Library to print version and build number
*/

#include <iostream>
#include "version_library.h"

namespace HW_01
{

/*!
Print Version and build number
\return build number
*/
int version()
{
    #ifdef PROJECT_VERSION_MINOR
	std::cout << "Version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR << "." << PROJECT_VERSION_PATCH << std::endl;
	#else
	std::cout << "Version " << PROJECT_VERSION_MAJOR << "." << 0  << "." << PROJECT_VERSION_PATCH << std::endl;
	#endif
	return PROJECT_VERSION_PATCH;
}

}
