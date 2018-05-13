#pragma once

#include "basics.h"

namespace HW_05
{

class Ellipse:
	public IElement
{
public:
	Ellipse():
		ellipse
		{
			Point(0,0),
			Point(0,0),
			Point(0,0),
			Point(0,0)
		}
	{}

	Ellipse(Point left, Point right, Point up, Point down):
		ellipse
		{
			left,
			right,
			up,
			down
		}
	{}

	Point Get_Coordinate() override
	{}

private:
    std::vector<Point> ellipse;

};


class Circle:
	public IElement
{
public:
	Circle():
		circle
		({
			Point(0,0),
			Point(0,0),
			Point(0,0),
			Point(0,0)
		})
	{}

	Circle(Point center, int64_t radius):
		circle
		({
            Point(center.first + radius, center.second + radius),
            Point(center.first + radius, center.second + radius),
            Point(center.first + radius, center.second + radius),
            Point(center.first + radius, center.second + radius)
		})
	{}

	Point Get_Coordinate() override
	{}

private:
	Ellipse circle;
};

}
