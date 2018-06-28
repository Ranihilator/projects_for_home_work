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

#include <iostream>
#include <string>

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

	Editor editor;

	editor.Create_Document("new");
	editor.Save_Document("new", "new.cdr");
	editor.Close_Document("new");

	editor.Create_Document("new1");
	editor.Select_Workspace("new1");
	editor.Create_Shape(std::unique_ptr<SHAPES::IShape>(new SHAPES::Point()));

	SHAPES::IShape* ptr = editor.Select_Shape({0,0});
	ptr->Set_Color(SHAPES::Color_RGB(126,0,0));
	editor.Save_Document("new1", "new1.cdr");

	editor.Delete_Shape({0,0});
	editor.Close_Document("new1");

	editor.Load_Document("new2", "new.cdr");
	editor.Close_Document("new2");

	return 0;
}

