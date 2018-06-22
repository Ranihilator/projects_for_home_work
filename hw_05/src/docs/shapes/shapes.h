#pragma once

#include "elements/ishapes.h"
#include "elements/points.h"
#include "elements/lines.h"
#include "elements/polygons.h"
#include "elements/circles.h"

#include <map>
#include <memory>

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Shapes creator
*/
class Shapes
{
public:
	void insert(IShape *shape);
	void replace(uint64_t ID, IShape *shape);
	void replace(Coordinate_XY coordinate, IShape *shape);

	IShape* find(uint64_t ID);
	IShape* find(Coordinate_XY coordinate);

	bool remove(uint64_t ID);
	bool remove(Coordinate_XY coordinate);

	size_t size();

	void clear();

private:
	std::map<uint64_t, std::unique_ptr<IShape>> shapes;
};

}

}
