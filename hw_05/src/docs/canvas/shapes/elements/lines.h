#pragma once

#include "ishape.h"
#include "points.h"

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Polyline primitive
\details provide polyline constructor
*/
class Polyline:
	public IShape
{
public:

	/*!
	\brief Polyline
	\param[in] args - array SHAPES::Coordinate_XY to construct polyline
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Polyline(std::initializer_list<Coordinate_XY> args, Color_RGB _color);

	/*!
	\brief Get polyline coordinate
	\details Get center of polylne
	\return return SHAPES::Coordinate_XY
	*/
	Coordinate_XY Get_Coordinate() const override;

	/*!
	\brief Get color
	\return return SHAPES::Color_RGB
	*/
	Color_RGB Get_Color() const override;

	/*!
	\brief Set new polyline color
	\param[in] _color - new color code SHAPES::Color_RGB
	*/
	void Set_Color(Color_RGB _color) override;

	/*!
	\brief Set new polyline center coordinate
	\param[in] _coordinate - new coordinate SHAPES::Coordinate_XY
	*/
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	/*!
	\brief Try to select polyline
	\param[in] _coordinate - selected cursor position
	\return result of select
	*/
	bool Select(Coordinate_XY _coordinate) const override;

private:
	std::vector<Coordinate_XY> polyline;											///< Line array SHAPES::Coordinate_XY
	Color_RGB color;																///< Current SHAPES::Color_RGB
};

/*!
\brief Line primitive
\details provide line constructor inheriting from Polyline
*/
class Line:
	public Polyline
{
public:
	/*!
	\brief Default Line
	*/
	Line();

	/*!
	\brief Line
	\param[in] point_1 - Begin line
	\param[in] point_2 - End line
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Line(Coordinate_XY point_1, Coordinate_XY point_2, Color_RGB _color);
};

}

}
