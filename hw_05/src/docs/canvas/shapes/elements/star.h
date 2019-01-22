#pragma once

#include "polygons.h"

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Star primitive
\details provide star constructor inheriting from Polygon
*/
class Star :
	public Polygon
{
public:

	/*!
	\brief Default Star
	*/
	Star();

	/*!
	\brief Star
	\param[in] star_center - SHAPES::Coordinate_XY center of Star shape
	\param[in] size - size of Square
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Star(Coordinate_XY star_center, int64_t size, Color_RGB _color);
};

}

}

