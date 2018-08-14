#pragma once

#include "elements/points.h"
#include "elements/lines.h"
#include "elements/polygons.h"
#include "elements/circles.h"

#include <map>
#include <memory>

namespace HW_05
{

/*!
\brief Shapes namespace
\details Provide SHAPES::Shapes creator class to construct shapes
and shapes class primitive
*/
namespace SHAPES
{

/*!
\brief Shapes creator class to construct shapes
\details Creator collecting shapes and can operating with them such (insert, find, replace, remove and clear)
*/
class Shapes
{
public:

	/*!
	\brief insert shape
	\param[in] shape - create shape
	*/
	void insert(IShape* shape);

	/*!
	\brief replace shape by ID
	\param[in] ID - Number of element
	\param[in] shape - new shape
	*/
	void replace(uint64_t ID, IShape *shape);

	/*!
	\brief replace shape by Coordinate
	\param[in] coordinate - SHAPES::Coordinate_XY
	\param[in] shape - new shape
	*/
	void replace(Coordinate_XY coordinate, IShape *shape);

	/*!
	\brief find shapes by ID
	\param[in] ID - Number of element
	\return pointer to Shape
	*/
	IShape* find(uint64_t ID);

	/*!
	\brief find shapes by coordinate
	\param[in] coordinate - SHAPES::Coordinate_XY
	\return pointer to Shape
	*/
	IShape* find(Coordinate_XY coordinate);

	/*!
	\brief remove shapes by ID
	\param[in] ID - Number of element
	\return operation status
	*/
	bool remove(uint64_t ID);

	/*!
	\brief remove shapes by coordinate
	\param[in] coordinate - SHAPES::Coordinate_XY
	\return operation status
	*/
	bool remove(Coordinate_XY coordinate);

	/*!
	\brief size of shapes pool
	\return Count of shapes
	*/
	size_t size();

	/*!
	\brief clear shapes pool
	*/
	void clear();

private:
	std::map<uint64_t, std::unique_ptr<IShape>> shapes;			///< Shapes pool
};

}

}
