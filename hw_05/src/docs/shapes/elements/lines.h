#pragma once

#include "ishapes.h"
#include "points.h"

namespace HW_05
{

namespace SHAPES
{

class Polyline:
	public IShape
{
public:
	Polyline(std::initializer_list<Coordinate_XY> args, Color_RGB _color);

	Coordinate_XY Get_Coordinate() const override;
	Color_RGB Get_Color() const override;

	void Set_Color(Color_RGB _color) override;
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	bool Select(Coordinate_XY _coordinate) const override;
	void Draw() override;

private:
	std::vector<Coordinate_XY> polyline;
	Color_RGB color;
};

class Line:
	public Polyline
{
public:
	Line();
	Line(Coordinate_XY point_1, Coordinate_XY point_2, Color_RGB _color);
};

}

}
