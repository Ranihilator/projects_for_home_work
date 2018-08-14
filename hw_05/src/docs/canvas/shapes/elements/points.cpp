#include "points.h"

namespace HW_05
{

namespace SHAPES
{

Point::Point():
	coordinate(Default_Coordinate), color(Default_Color)
{}

Point::Point(Coordinate_XY _coordinate, Color_RGB _color):
	coordinate(_coordinate), color(_color)
{}

Coordinate_XY Point::Get_Coordinate() const
{
	return this->coordinate;
}

Color_RGB Point::Get_Color() const
{
	return this->color;
}

uint64_t Point::Get_Size() const
{
	return 0;
}

void Point::Set_Color(Color_RGB _color)
{
	this->color = _color;
}

void Point::Set_Coordinate(Coordinate_XY _coordinate)
{
	this->coordinate = _coordinate;
}

void Point::Set_Size(uint64_t _size)
{
}

bool Point::Select(Coordinate_XY _coordinate) const
{
	if (_coordinate == this->coordinate)
		return true;

	return false;
}


}

}
