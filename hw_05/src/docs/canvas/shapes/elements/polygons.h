#pragma once

#include "points.h"

namespace HW_05
{

namespace SHAPES
{

/*!
\brief Polygon primitive
\details provide polygon constructor
*/
class Polygon:
	public IShape
{
public:

	/*!
	\brief Default Polygon
	*/
	Polygon();

	/*!
	\brief Polygon
	\param[in] args - array SHAPES::Coordinate_XY to construct Polygon
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Polygon(std::initializer_list<Coordinate_XY> args, Color_RGB _color);

	/*!
	\brief Get Polygon center coordinate
	\return return SHAPES::Coordinate_XY
	*/
	Coordinate_XY Get_Coordinate() const override;

	/*!
	\brief Get color
	\return return SHAPES::Color_RGB
	*/
	Color_RGB Get_Color() const override;

	/*!
	\brief Getting the size of Polygon
	\return size of Polygon
	*/
	uint64_t Get_Size() const override;

	/*!
	\brief Set new color
	\param[in] _color - new color code SHAPES::Color_RGB
	*/
	void Set_Color(Color_RGB _color) override;

	/*!
	\brief Set new polygon center coordinate
	\param[in] _coordinate - new coordinate SHAPES::Coordinate_XY
	*/
	void Set_Coordinate(Coordinate_XY _coordinate) override;

	/*!
	\brief Setting the size of Polygon
	\param[in] _size - size of Polygon
	*/
	void Set_Size(uint64_t _size) override;

	/*!
	\brief Try to select Polygon
	\param[in] _coordinate - selected cursor position
	\return result of select
	*/
	bool Select(Coordinate_XY _coordinate) const override;

private:
	std::vector<Coordinate_XY> polygon;												///< Line array SHAPES::Coordinate_XY
	Color_RGB color;																///< Current SHAPES::Color_RGB
};

/*!
\brief Rectangle primitive
\details provide rectangle constructor inheriting from Polygon
*/
class Rectangle:
	public Polygon
{
public:

	/*!
	\brief Default Rectangle
	*/
	Rectangle();

	/*!
	\brief Rectangle
	\param[in] down_left_cornet - SHAPES::Coordinate_XY down_left_cornet Rectangle
	\param[in] up_right_cornet - SHAPES::Coordinate_XY up_right_cornet Rectangle
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Rectangle(Coordinate_XY down_left_cornet, Coordinate_XY up_right_cornet, Color_RGB _color);
};

/*!
\brief Square primitive
\details provide square constructor inheriting from Polygon
*/
class Square :
	public Polygon
{
public:

	/*!
	\brief Default Square
	*/
	Square();

	/*!
	\brief Square
	\param[in] down_left_corner - SHAPES::Coordinate_XY down_left_corner Square
	\param[in] size - size of Square
	\param[in] _color - color SHAPES::Color_RGB
	*/
	Square(Coordinate_XY down_left_corner, int64_t size, Color_RGB _color);
};

}

}
