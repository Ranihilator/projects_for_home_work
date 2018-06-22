#include "polygons.h"

namespace HW_05
{

namespace SHAPES
{

Polygon::Polygon():
	polygon(), color(Default_Color)
{}

Polygon::Polygon(std::initializer_list<Coordinate_XY> args, Color_RGB _color):
	polygon(args), color(_color)
{}

Coordinate_XY Polygon::Get_Coordinate() const
{
	Coordinate_XY _coordinate;
	for (auto &i : this->polygon)
	{
		std::get<0>(_coordinate) += std::get<0>(i);
		std::get<1>(_coordinate) += std::get<1>(i);
	}
	std::get<0>(_coordinate) /= this->polygon.size();
	std::get<1>(_coordinate) /= this->polygon.size();

	return _coordinate;
}

Color_RGB Polygon::Get_Color() const
{
	return this->color;
}

void Polygon::Set_Color(Color_RGB _color)
{
	this->color = _color;
}

void Polygon::Set_Coordinate(Coordinate_XY _coordinate)
{
	Coordinate_XY _coord;
	for (auto &i : this->polygon)
	{
		std::get<0>(_coord) += std::get<0>(i);
		std::get<1>(_coord) += std::get<1>(i);
	}
	std::get<0>(_coord) /= this->polygon.size();
	std::get<1>(_coord) /= this->polygon.size();

	std::get<0>(_coord) -= std::get<0>(_coordinate);
	std::get<1>(_coord) -= std::get<1>(_coordinate);

	for (auto &i : this->polygon)
	{
		std::get<0>(i) += std::get<0>(_coord);
		std::get<1>(i) += std::get<1>(_coord);
	}
}

bool Polygon::Select(Coordinate_XY _coordinate) const
{
	Coordinate_XY _coord;
	for (auto &i : this->polygon)
	{
		std::get<0>(_coord) += std::get<0>(i);
		std::get<1>(_coord) += std::get<1>(i);
	}
	std::get<0>(_coord) /= this->polygon.size();
	std::get<1>(_coord) /= this->polygon.size();

	if (_coord == _coordinate)
		return true;

	return false;
}

void Polygon::Draw()
{}



Rectangle::Rectangle():
	Polygon()
{}

Rectangle::Rectangle(Coordinate_XY down_left_cornet, Coordinate_XY up_right_cornet):
	Polygon
	({
		down_left_cornet,
		Coordinate_XY(std::get<0>(up_right_cornet), 0),
		up_right_cornet,
		Coordinate_XY(0, std::get<1>(down_left_cornet))
	}, Default_Color)
{}



Square::Square()
{}

Square::Square(Coordinate_XY down_left_corner, int64_t size):
	Polygon
	({
		down_left_corner,
		Coordinate_XY(std::get<0>(down_left_corner) + size, std::get<0>(down_left_corner) + size)
	}, Default_Color)
{}

}

}
