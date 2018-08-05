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

}


BOOST_AUTO_TEST_CASE(test_canvas_controller)
{

}

BOOST_AUTO_TEST_CASE(test_docs_controller)
{

}

BOOST_AUTO_TEST_CASE(test_editor_controller)
{

}

BOOST_AUTO_TEST_SUITE_END()
