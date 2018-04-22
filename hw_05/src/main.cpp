/*!
\file
\brief Create UML diagram from simple vector graph editor

Simple UML design functional:
Create new documents
Import documents from file
Export documents to file
Create simple graph elements
*/

#include "version_library.h"
#include "editor.h"

using namespace HW_05;

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
			std::cout << "	simple_uml without arguments to run" << std::endl;
			std::cout << "	simple_uml -v Current version print" << std::endl;
			std::cout << std::endl;
		}



		return 0;
    }
}

