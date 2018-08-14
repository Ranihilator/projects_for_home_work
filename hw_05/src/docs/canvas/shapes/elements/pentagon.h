#pragma once

#include "polygons.h"

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Pentagon primitive
\details provide star constructor inheriting from Polygon
*/
class Pentagon :
	public Polygon
{
public:

	/*!
	\brief Default Pentagon
	*/
	Pentagon();

	/*!
	\brief Pentagon
	\param[in] star_center - SHAPES::Coordinate_XY center of Pentagon shape
	\param[in] size - size of Square
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Pentagon(Coordinate_XY star_center, int64_t size, Color_RGB _color);
};

}

}


