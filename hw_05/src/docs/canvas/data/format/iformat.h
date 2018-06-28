#pragma once

#include <string>
#include "shapes.h"
#include <fstream>


namespace HW_05
{

namespace DATA_STORAGE
{

enum class FORMATS
{
	NUL,
	CDR,
	DXF,
	SVG,
	VSD
};

class IFORMAT
{
public:
	virtual void Import(SHAPES::Shapes *shape) = 0;
	virtual void Export(SHAPES::Shapes *shape) = 0;
};

}

}
