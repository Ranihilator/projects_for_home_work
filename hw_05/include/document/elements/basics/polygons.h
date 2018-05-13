#pragma once

#include "basics.h"

namespace HW_05
{

class Polygon:
	public IElement
{
public:
	Polygon():
		polygon()
	{}

	Polygon(std::initializer_list<Point> args):
		polygon(args)
	{}

	Point Get_Coordinate() override
	{}

private:
	std::vector<Point> polygon;
};

class Rectangle:
	public IElement
{
public:
	Rectangle():
		rectangle()
	{}

	Rectangle(Point down_left_cornet, Point up_right_cornet):
		rectangle
		({
			down_left_cornet,
			Point(up_right_cornet.first,0),
			up_right_cornet,
			Point(0,down_left_cornet.second)
		})
	{}

	Point Get_Coordinate() override
	{}

private:
	Polygon rectangle;
};

class Square :
	public IElement
{
public:
	Square()
	{}

	Square(Point down_left_corner, int64_t size):
		square
		(
			down_left_corner,
			Point(down_left_corner.first + size, down_left_corner.second + size)
		)
	{}

	Point Get_Coordinate() override
	{}

private:
	Rectangle square;
};

}
