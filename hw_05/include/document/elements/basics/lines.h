#pragma once

#include "basics.h"

namespace HW_05
{

class Polyline:
	public IElement
{
public:
	Polyline(std::initializer_list<Point> args):
		polyline(args)
	{}

	Point Get_Coordinate() override
	{}
private:
	std::vector<Point> polyline;
};

class Line:
	public IElement
{
public:
	Line():
		line({Point(0, 0), Point(0, 0)})
	{}

	Line(Point pos_1, Point pos_2):
		line({pos_1, pos_2})
	{}

	Point Get_Coordinate() override
	{}

private:
	Polyline line;
};

}
