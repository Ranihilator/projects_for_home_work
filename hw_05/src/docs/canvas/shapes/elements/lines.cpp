#include "lines.h"

namespace HW_05
{

namespace SHAPES
{

Polyline::Polyline(std::initializer_list<Coordinate_XY> args, Color_RGB _color):
	polyline(args), color(_color)
{}

Coordinate_XY Polyline::Get_Coordinate() const
{
	Coordinate_XY _coordinate;
	for (auto &i : this->polyline)
	{
		std::get<0>(_coordinate) += std::get<0>(i);
		std::get<1>(_coordinate) += std::get<1>(i);
	}
	std::get<0>(_coordinate) /= this->polyline.size();
	std::get<1>(_coordinate) /= this->polyline.size();

	return _coordinate;
}

Color_RGB Polyline::Get_Color() const
{
	return this->color;
}

void Polyline::Set_Color(Color_RGB _color)
{
	this->color = _color;
}

void Polyline::Set_Coordinate(Coordinate_XY _coordinate)
{
	Coordinate_XY _coord;
	for (auto &i : this->polyline)
	{
		std::get<0>(_coord) += std::get<0>(i);
		std::get<1>(_coord) += std::get<1>(i);
	}
	std::get<0>(_coord) /= this->polyline.size();
	std::get<1>(_coord) /= this->polyline.size();

	std::get<0>(_coord) -= std::get<0>(_coordinate);
	std::get<1>(_coord) -= std::get<1>(_coordinate);

	for (auto &i : this->polyline)
	{
		std::get<0>(i) += std::get<0>(_coord);
		std::get<1>(i) += std::get<1>(_coord);
	}
}

bool Polyline::Select(Coordinate_XY _coordinate) const
{
	Coordinate_XY _coord;
	for (auto &i : this->polyline)
	{
		std::get<0>(_coord) += std::get<0>(i);
		std::get<1>(_coord) += std::get<1>(i);
	}
	std::get<0>(_coord) /= this->polyline.size();
	std::get<1>(_coord) /= this->polyline.size();

	if (_coord == _coordinate)
		return true;

	return false;
}



Line::Line():
	Polyline({Coordinate_XY(Default_Coordinate), Coordinate_XY(Default_Coordinate)}, Default_Color)
{}

Line::Line(Coordinate_XY point_1, Coordinate_XY point_2, Color_RGB _color):
	Polyline({point_1, point_2}, _color)
{}

}

}
