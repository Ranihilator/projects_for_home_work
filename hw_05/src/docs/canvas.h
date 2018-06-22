#pragma once

#include "shapes/shapes.h"
#include "data/file.h"

namespace HW_05
{

namespace DOCUMENTS
{

/*!
\brief Indirection Canvas
\details Canvas workspace
*/
class Canvas
{
public:

private:
	std::string name;

	SHAPES::Shapes shapes;

	SHAPES::Coordinate_XY canvas_size;
	SHAPES::Coordinate_XY center_coordinate;
};

}

}
