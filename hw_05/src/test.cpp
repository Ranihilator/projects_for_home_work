/*! \file
	\brief Test for UML_Example
*/
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE simple_uml_test

#include <boost/test/unit_test.hpp>

#include "editor.h"

BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_05;
using namespace HW_05::SHAPES;
using namespace HW_05::DATA_STORAGE;
using namespace HW_05::DOCUMENTS;

BOOST_AUTO_TEST_CASE(test_shapes)
{
	std::unique_ptr<IShape> shape;

	shape.reset(new Point());
	BOOST_CHECK(shape->Get_Coordinate() == Default_Coordinate);
	BOOST_CHECK(shape->Get_Color() == Default_Color);
	BOOST_CHECK(shape->Get_Size() == 0);
	BOOST_CHECK(shape->Select(Coordinate_XY(0, 0)));
	BOOST_CHECK(!shape->Select(Coordinate_XY(1, 2)));

	shape->Set_Coordinate(Coordinate_XY(10, 20));
	BOOST_CHECK(shape->Get_Coordinate() == Coordinate_XY(10, 20));
	BOOST_CHECK(shape->Select(Coordinate_XY(10, 20)));
	BOOST_CHECK(!shape->Select(Coordinate_XY(1, 2)));

	shape->Set_Color(Color_RGB(127, 127, 5));
	BOOST_CHECK(shape->Get_Color() == Color_RGB(127, 127, 5));

	shape->Set_Size(10);
	BOOST_CHECK(shape->Get_Size() == 0);

	shape.reset(new Point(Coordinate_XY(5,5), Color_RGB(127, 5, 1)));
	BOOST_CHECK(shape->Get_Coordinate() == Coordinate_XY(5,5));
	BOOST_CHECK(shape->Get_Color() == Color_RGB(127, 5, 1));
	BOOST_CHECK(shape->Get_Size() == 0);
	BOOST_CHECK(shape->Select(Coordinate_XY(5,5)));
	BOOST_CHECK(!shape->Select(Coordinate_XY(1, 2)));

	shape->Set_Coordinate(Coordinate_XY(10, 20));
	BOOST_CHECK(shape->Get_Coordinate() == Coordinate_XY(10, 20));
	BOOST_CHECK(shape->Select(Coordinate_XY(10, 20)));
	BOOST_CHECK(!shape->Select(Coordinate_XY(1, 2)));

	shape->Set_Color(Color_RGB(127, 127, 5));
	BOOST_CHECK(shape->Get_Color() == Color_RGB(127, 127, 5));

	shape->Set_Size(10);
	BOOST_CHECK(shape->Get_Size() == 0);

	///Repeat test for Lines, Circles, Polygons and other shapes
}

BOOST_AUTO_TEST_CASE(test_shapes_controller)
{
	SHAPES::Shapes controller;

	controller.insert(new SHAPES::Point());
	controller.insert(new SHAPES::Point(Coordinate_XY(5, 5), Color_RGB(127, 5, 1)));
	controller.insert(new SHAPES::Line(Coordinate_XY(0, 0), Coordinate_XY(5, 5), Color_RGB(127, 52, 25)));
	controller.insert(new SHAPES::Circle(Coordinate_XY(50, 50), 32, Color_RGB(127, 127, 127)));

	BOOST_CHECK(controller.size() == 4);

	controller.replace(Coordinate_XY(5, 5), new SHAPES::Polyline({Coordinate_XY(5, 5), Coordinate_XY(5, 10), Coordinate_XY(10, 5), Coordinate_XY(20, 20)}, Color_RGB(255, 255, 255)));

	BOOST_CHECK(controller.size() == 4);

	controller.replace(3, new SHAPES::Point());

	BOOST_CHECK(controller.size() == 4);

	auto ptr = controller.find(Coordinate_XY(5, 5));
	if (ptr)
		BOOST_CHECK(ptr->Get_Color() == Color_RGB(255, 255, 255));
	else
		BOOST_ERROR("shapes not found");

	controller.clear();
	BOOST_CHECK(controller.size() == 0);
}

BOOST_AUTO_TEST_CASE(test_file_format_parser)
{
	SHAPES::Shapes controller;

	std::vector<uint8_t> svg_sample = {};
	svg svg_parser(svg_sample);

	///Repeat test for cdr, dxf, vsd format

	svg_parser.Import(&controller);

	BOOST_CHECK(controller.size() == 4);
	auto ptr = controller.find(Coordinate_XY(5, 5));
	if (ptr)
		BOOST_CHECK(ptr->Get_Color() == Color_RGB(255, 255, 255));
	else
		BOOST_ERROR("shapes not found");

	///Etc shapes dependency on binary sample
}

BOOST_AUTO_TEST_CASE(test_data_link_storage)
{
	///Work with file's
	SHAPES::Shapes controller;
	std::string path = "~/1.vsd";

	Data_Link database(path, &controller);

	BOOST_CHECK (controller.size() == 4);

	path = "~/2.cdr";

	database.Import(path);

	BOOST_CHECK (controller.size() == 8);

	///find and checks loaded shapes, from controller

	controller.insert(new SHAPES::Point()); //insert new shapes

	path = "~/3.dxf";
	database.Export(path);//save shapes from controller;

	///works with database
	SHAPES::Shapes controller_sql;
	Data_Link sql_database("127.0.0.1:599", "oracle", "user", "password", &controller_sql);

	BOOST_CHECK (controller_sql.size() == 5);

	std::string path_sql = "192.168.0.1:599";
	sql_database.Import(path_sql);

	BOOST_CHECK (controller_sql.size() == 10);

	path_sql = "163.0.0.1:2700";
	controller_sql.insert(new SHAPES::Point());
	sql_database.Export(path_sql);
}


BOOST_AUTO_TEST_CASE(test_canvas_controller)
{
	Canvas canvas; // canvas("file url")

	canvas.insert(new SHAPES::Point());
	canvas.insert(new SHAPES::Line());

	canvas.Export("~/1.cdr");

	canvas.clear();

	canvas.Import("~/2.dxf");

	BOOST_CHECK(canvas.size() == 4);

	auto ptr = canvas.find(Coordinate_XY(0, 0));
	if (ptr)
		BOOST_CHECK(ptr->Get_Color() == Color_RGB(255, 255, 255));
	else
		BOOST_ERROR("shapes not found");

	Canvas canvas_sql("127.0.0.1:599", "oracle", "user", "password");

	/// use inherited Shapes controller to work with shapes on sql database
}

BOOST_AUTO_TEST_CASE(test_docs_controller)
{
	Docs docs;

	docs.insert("new_documents", "~/1.cdr");

	Canvas *ptr = docs.find("new_documents");

	if (ptr)
	{
		ptr->insert(new SHAPES::Point());
		ptr->insert(new SHAPES::Line());
	}

	docs.insert("test" "127.0.0.1:599");

	Canvas *ptr_sql = docs.find("test");

	if(ptr_sql)
	{
		ptr_sql->insert(new SHAPES::Point());
		ptr_sql->insert(new SHAPES::Line());
	}

	docs.Save("new_documents", "~/1.cdr");
	docs.Save("test", "~/2.svg");

	docs.Load("test", "127.0.0.1:599");

	docs.find("test")->find(Coordinate_XY(0, 0));

}

BOOST_AUTO_TEST_CASE(test_editor_controller)
{
	Editor editor;

	editor.Create_Document("new");
	editor.Save_Document("new", "new.cdr");
	editor.Close_Document("new");

	editor.Create_Document("new1");
	editor.Select_Workspace("new1");
	editor.Create_Shape(new SHAPES::Point());

	SHAPES::IShape* ptr = editor.Select_Shape({0,0});
	ptr->Set_Color(SHAPES::Color_RGB(126,0,0));
	editor.Save_Document("new1", "new1.cdr");

	editor.Delete_Shape({0,0});
	editor.Close_Document("new1");

	editor.Load_Document("new2", "new.cdr");
	editor.Close_Document("new2");
}

BOOST_AUTO_TEST_SUITE_END()
