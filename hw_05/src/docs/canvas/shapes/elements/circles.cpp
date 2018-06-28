#include "circles.h"

namespace HW_05
{

namespace SHAPES
{

Ellipse::Ellipse()
{}

Ellipse::Ellipse(Coordinate_XY left, Coordinate_XY right, Coordinate_XY up, Coordinate_XY down, Color_RGB _color):
	ellipse({left, right, up, down}), color(_color)
{}

Coordinate_XY Ellipse::Get_Coordinate() const
{
	Coordinate_XY _coordinate;
	for (auto &i : this->ellipse)
	{
		std::get<0>(_coordinate) += std::get<0>(i);
		std::get<1>(_coordinate) += std::get<1>(i);
	}
	std::get<0>(_coordinate) /= this->ellipse.size();
	std::get<1>(_coordinate) /= this->ellipse.size();

	return _coordinate;
}

Color_RGB Ellipse::Get_Color() const
{
	return this->color;
}

void Ellipse::Set_Color(Color_RGB _color)
{
	this->color = _color;
}

void Ellipse::Set_Coordinate(Coordinate_XY _coordinate)
{
	Coordinate_XY _coord;
	for (auto &i : this->ellipse)
	{
		std::get<0>(_coord) += std::get<0>(i);
		std::get<1>(_coord) += std::get<1>(i);
	}
	std::get<0>(_coord) /= this->ellipse.size();
	std::get<1>(_coord) /= this->ellipse.size();

	std::get<0>(_coord) -= std::get<0>(_coordinate);
	std::get<1>(_coord) -= std::get<1>(_coordinate);

	for (auto &i : this->ellipse)
	{
		std::get<0>(i) += std::get<0>(_coord);
		std::get<1>(i) += std::get<1>(_coord);
	}
}

bool Ellipse::Select(Coordinate_XY _coordinate) const
{
	Coordinate_XY _coord;
	for (auto &i : this->ellipse)
	{
		std::get<0>(_coord) += std::get<0>(i);
		std::get<1>(_coord) += std::get<1>(i);
	}
	std::get<0>(_coord) /= this->ellipse.size();
	std::get<1>(_coord) /= this->ellipse.size();

	if (_coord == _coordinate)
		return true;

	return false;
}

void Ellipse::Draw()
{}


Circle::Circle():
	Ellipse()
{}

Circle::Circle(Coordinate_XY center, int64_t radius, Color_RGB _color):
	Ellipse	(
		Coordinate_XY(std::get<0>(center) + radius, std::get<1>(center) + radius),
		Coordinate_XY(std::get<0>(center) + radius, std::get<1>(center) + radius),
		Coordinate_XY(std::get<0>(center) + radius, std::get<1>(center) + radius),
		Coordinate_XY(std::get<0>(center) + radius, std::get<1>(center) + radius),
		_color
		)
{}

}

}
