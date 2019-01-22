#include "star.h"

namespace HW_05
{

namespace SHAPES
{

Star::Star()
{}

Star::Star(Coordinate_XY star_center, int64_t size, Color_RGB _color):
	Polygon
	({
		//Coordinate_XY(std::get<0>(star_center) + size, std::get<0>(star_center) + 0)
		//Place to variable template Coordinate_XY to form Star shape
	}, _color)
{}

}

}
