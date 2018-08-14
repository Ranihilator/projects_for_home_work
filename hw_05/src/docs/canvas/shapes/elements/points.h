#pragma once

#include "ishape.h"

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Point primitive
\details provide point constructor
*/
class Point:
	public IShape
{
public:

	/*!
	\brief Default point
	*/
	Point();

	/*!
	\brief Point
	\param[in] _coordinate - point SHAPES::Coordinate_XY
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Point(Coordinate_XY _coordinate, Color_RGB _color);

	/*!
	\brief Get point coordinate
	\return return SHAPES::Coordinate_XY
	*/
	Coordinate_XY Get_Coordinate() const override;

	/*!
	\brief Get color
	\return return SHAPES::Color_RGB
	*/
	Color_RGB Get_Color() const override;

	/*!
	\brief Set new point color
	\param[in] _color - new color code SHAPES::Color_RGB
	*/
	void Set_Color(Color_RGB _color) override;

	/*!
	\brief Set new point coordinate
	\param[in] _coordinate - new coordinate SHAPES::Coordinate_XY
	*/
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	/*!
	\brief Try to select point
	\param[in] _coordinate - selected cursor position
	\return result of select
	*/
	bool Select(Coordinate_XY _coordinate) const override;

private:
	Coordinate_XY coordinate;											///< Current SHAPES::Coordinate_XY
	Color_RGB color;													///< Current SHAPES::Color_RGB
};

}

}
