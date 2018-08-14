#pragma once

#include "points.h"

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Ellipse primitive
\details provide ellipse constructor
*/
class Ellipse:
	public IShape
{
public:

	/*!
	\brief Default Ellipse
	*/
	Ellipse();

	/*!
	\brief Ellipse
	\param[in] left - SHAPES::Coordinate_XY left ellipse coordinate
	\param[in] right - SHAPES::Coordinate_XY right ellipse coordinate
	\param[in] up - SHAPES::Coordinate_XY up ellipse coordinate
	\param[in] down - SHAPES::Coordinate_XY down ellipse coordinate
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Ellipse(Coordinate_XY left, Coordinate_XY right, Coordinate_XY up, Coordinate_XY down, Color_RGB _color);

	/*!
	\brief Get Ellipse center coordinate
	\return return SHAPES::Coordinate_XY
	*/
	Coordinate_XY Get_Coordinate() const override;

	/*!
	\brief Get color
	\return return SHAPES::Color_RGB
	*/
	Color_RGB Get_Color() const override;

	/*!
	\brief Getting the size of Ellipse
	\return size of Ellipse
	*/
	uint64_t Get_Size() const override;

	/*!
	\brief Set new color
	\param[in] _color - new color code SHAPES::Color_RGB
	*/
	void Set_Color(Color_RGB _color) override;

	/*!
	\brief Set new ellipse center coordinate
	\param[in] _coordinate - new coordinate SHAPES::Coordinate_XY
	*/
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	/*!
	\brief Setting the size of Ellipse
	\param[in] _size - size of Ellipse
	*/
	void Set_Size(uint64_t _size) override;

	/*!
	\brief Try to select Ellipse
	\param[in] _coordinate - selected cursor position
	\return result of select
	*/
	bool Select(Coordinate_XY _coordinate) const override;

private:
	std::vector<Coordinate_XY> ellipse;
	Color_RGB color;
};

/*!
\brief Circle primitive
\details provide circle constructor inheriting from Ellipse
*/
class Circle:
	public Ellipse
{
public:

	/*!
	\brief Default Circle
	*/
	Circle();

	/*!
	\brief Circle
	\param[in] center - SHAPES::Coordinate_XY left circle coordinate
	\param[in] - radius - radius circle
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Circle(Coordinate_XY center, int64_t radius, Color_RGB _color);
};

}

}
