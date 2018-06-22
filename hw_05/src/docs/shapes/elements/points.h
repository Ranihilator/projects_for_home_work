#pragma once

#include "ishapes.h"

namespace HW_05
{

namespace SHAPES
{

class Point:
	public IShape
{
public:
	Point();
	Point(Coordinate_XY _coordinate, Color_RGB _color);

	Coordinate_XY Get_Coordinate() const override;
	Color_RGB Get_Color() const override;

	void Set_Color(Color_RGB _color) override;
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	bool Select(Coordinate_XY _coordinate) const override;
	void Draw() override;

private:
	Coordinate_XY coordinate;
	Color_RGB color;
};

}

}
