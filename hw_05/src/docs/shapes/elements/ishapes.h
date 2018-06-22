#pragma once

#include <cstdint>
#include <tuple>
#include <vector>

namespace HW_05
{

namespace SHAPES
{

using Coordinate_XY = std::tuple<int64_t, int64_t>;
using Color_RGB = std::tuple<uint8_t, uint8_t, uint8_t>;

static const auto Default_Coordinate = Coordinate_XY(0, 0);
static const auto Default_Color = Color_RGB(0, 0, 0);

static const auto BLUE = Color_RGB(0, 0, 255);
static const auto CYAN = Color_RGB(0, 255, 255);
static const auto GOLD = Color_RGB(255, 215, 0);
static const auto GREEN = Color_RGB(0, 128, 0);
static const auto GREY = Color_RGB(128, 128, 128);
static const auto MAROON = Color_RGB(128, 0, 0);
static const auto ORANGE = Color_RGB(255, 165, 0);
static const auto PINK = Color_RGB(255, 192, 203);
static const auto PURPLE = Color_RGB(128, 0, 128);
static const auto RED = Color_RGB(255, 0, 0);
static const auto SILVER = Color_RGB(192, 192, 192);
static const auto TEAL = Color_RGB(0, 128, 128);
static const auto TURQUOISE = Color_RGB(64, 224, 208);
static const auto WHITE = Color_RGB(255, 255, 255);
static const auto YELLOW = Color_RGB(255, 255, 0);

/*!
\brief IShapes Polymorphism
*/
class IShape
{
public:
	virtual void Set_Color(Color_RGB color) = 0;
	virtual void Set_Coordinate(Coordinate_XY coord) = 0;
	virtual Coordinate_XY Get_Coordinate() const = 0;
	virtual Color_RGB Get_Color() const = 0;

	virtual bool Select(Coordinate_XY coord) const = 0;
	virtual void Draw() = 0;
};

}

}
