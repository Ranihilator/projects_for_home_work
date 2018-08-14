#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

namespace HW_05
{

namespace SHAPES
{

using Coordinate_XY = std::tuple<int64_t, int64_t>;							///< Coordinate of shapes (X and Y)
using Color_RGB = std::tuple<uint8_t, uint8_t, uint8_t>;					///< Color of shapes, code of RGB (Red, Green, Blue)

static const auto Default_Coordinate = Coordinate_XY(0, 0);					///< Default coordinate
static const auto Default_Color = Color_RGB(0, 0, 0);						///< Default color SHAPES::BLACK

static const auto BLACK = Color_RGB(0, 0, 0);								///< BLACK code
static const auto BLUE = Color_RGB(0, 0, 255);								///< BLUE code
static const auto CYAN = Color_RGB(0, 255, 255);							///< CYAN code
static const auto GOLD = Color_RGB(255, 215, 0);							///< GOLD code
static const auto GREEN = Color_RGB(0, 128, 0);								///< GREEN code
static const auto GREY = Color_RGB(128, 128, 128);							///< GREY code
static const auto MAROON = Color_RGB(128, 0, 0);							///< MAROON code
static const auto ORANGE = Color_RGB(255, 165, 0);							///< ORANGE code
static const auto PINK = Color_RGB(255, 192, 203);							///< PINK code
static const auto PURPLE = Color_RGB(128, 0, 128);							///< PURPLE code
static const auto RED = Color_RGB(255, 0, 0);								///< RED code
static const auto SILVER = Color_RGB(192, 192, 192);						///< SILVER code
static const auto TEAL = Color_RGB(0, 128, 128);							///< TEAL code
static const auto TURQUOISE = Color_RGB(64, 224, 208);						///< TURQUOISE code
static const auto WHITE = Color_RGB(255, 255, 255);							///< WHITE code
static const auto YELLOW = Color_RGB(255, 255, 0);							///< YELLOW code

/*!
\brief IShapes Polymorphism class
\details provide pure virtual method to shapes primitive
*/
class IShape
{
public:

	/*!
	\brief Setting the color of shape
	\param[in] color - SHAPES::Color_RGB code
	*/
	virtual void Set_Color(Color_RGB color) = 0;

	/*!
	\brief Setting the coordinate of shape
	\param[in] coord - SHAPES::Coordinate_XY coordinate
	*/
	virtual void Set_Coordinate(Coordinate_XY coord) = 0;

	/*!
	\brief Setting the size of shape
	\param[in] _size - size of shape
	*/
	virtual void Set_Size(uint64_t _size) = 0;

	/*!
	\brief Get the coordinate of shape
	\return SHAPES::Coordinate_XY coordinate
	*/
	virtual Coordinate_XY Get_Coordinate() const = 0;

	/*!
	\brief Get the color of shape
	\return SHAPES::Color_RGB code
	*/
	virtual Color_RGB Get_Color() const = 0;

	/*!
	\brief Getting the size of shape
	\return size of shape
	*/
	virtual uint64_t Get_Size() const = 0;

	/*!
	\brief Select figure to the coordinate
	\param[in] - coord - SHAPES::Coordinate_XY coordinate
	\return status of select
	*/
	virtual bool Select(Coordinate_XY coord) const = 0;
};

}

}
