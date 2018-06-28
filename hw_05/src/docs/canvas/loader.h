#pragma once

#include "shapes/shapes.h"
#include "data/file.h"

namespace HW_05
{

/*!
\brief Loader class indirect with DATA_STORAGE::File and SHAPES:Shapes
*/
class Loader
{
public:
	Loader();

private:
	SHAPE::Shapes* shapes;
    DATA_STORAGE::File* file;
};

}
