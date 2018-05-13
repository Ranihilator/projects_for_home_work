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
/*
    Editor editor;

    editor.Create_Document("untitled");
    editor["untitled"].Draw(new Line(0, 0, 5, 5));
	editor["untitled"].Delete(Point(0, 0));

	editor.Create_Document("untitled1");
    editor["untitled1"].Draw(new Circle(Point(0, 0), 10));
    editor["untitled1"].Draw(new Line(Point(0, 0), Point(5, 5)));
    editor["untitled1"].Delete(Point(0, 0));
    editor.Export(new FILE_FORMAT::dxf("file.dxf"));
    editor.Close_Document("untitled1");

    editor.Import(new FILE_FORMAT::svg("file.svg"));
    editor["file.svg"].Draw(new Polyline <Point, Point, Point> (Point(0, 0), Point(1, 1), Point(2, 2)));

    editor.Import(new FILE_FORMAT::cdr("file.cdr"));
	editor["file.cdr"].Draw(new Polygon <Point, Point, Point, Point> (Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 3)));
	editor.Close_Document("file.cdr");*/
}

