#pragma once

#include "ishape.h"
#include "points.h"

namespace HW_05
{

namespace SHAPES
{

class Ellipse:
	public IShape
{
public:
	Ellipse();
	Ellipse(Coordinate_XY left, Coordinate_XY right, Coordinate_XY up, Coordinate_XY down, Color_RGB _color);

	Coordinate_XY Get_Coordinate() const override;
	Color_RGB Get_Color() const override;

	void Set_Color(Color_RGB _color) override;
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	bool Select(Coordinate_XY _coordinate) const override;
	void Draw() override;

private:
	std::vector<Coordinate_XY> ellipse;
	Color_RGB color;
};


class Circle:
	public Ellipse
{
public:
	Circle();
	Circle(Coordinate_XY center, int64_t radius, Color_RGB _color);

private:
	Ellipse circle;
};

}

}
