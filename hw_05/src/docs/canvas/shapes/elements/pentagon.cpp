#include "pentagon.h"

namespace HW_05
{

namespace SHAPES
{

Pentagon::Pentagon()
{}

Pentagon::Pentagon(Coordinate_XY star_center, int64_t size, Color_RGB _color):
	Polygon
	({
		//Coordinate_XY(std::get<0>(star_center) + size, std::get<0>(star_center) + 0)
		//Place to variable template Coordinate_XY to form Pentagon shape
	}, _color)
{}

}

}

