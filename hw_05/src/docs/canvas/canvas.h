#pragma once

#include "shapes/shapes.h"
#include "data/file.h"

namespace HW_05
{

namespace DOCUMENTS
{

/*!
\brief Canvas workspace controller
*/
class Canvas:
	public SHAPES::Shapes
{
public:
	Canvas(std::string path = std::string());

	void Export(std::string path);
	void Import(std::string path);

private:
	DATA_STORAGE::File file;

private:
	SHAPES::Coordinate_XY canvas_size;
	SHAPES::Coordinate_XY canvas_center;
};

}

}
