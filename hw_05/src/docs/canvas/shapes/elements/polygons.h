#pragma once

#include "ishape.h"
#include "points.h"

namespace HW_05
{

namespace SHAPES
{

class Polygon:
	public IShape
{
public:
	Polygon();
	Polygon(std::initializer_list<Coordinate_XY> args, Color_RGB _color);

	Coordinate_XY Get_Coordinate() const override;
	Color_RGB Get_Color() const override;

	void Set_Color(Color_RGB _color) override;
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	bool Select(Coordinate_XY _coordinate) const override;
	void Draw() override;

private:
	std::vector<Coordinate_XY> polygon;
	Color_RGB color;
};

class Rectangle:
	public Polygon
{
public:
	Rectangle();
	Rectangle(Coordinate_XY down_left_cornet, Coordinate_XY up_right_cornet);
};

class Square :
	public Polygon
{
public:
	Square();
	Square(Coordinate_XY down_left_corner, int64_t size);
};

}

}
