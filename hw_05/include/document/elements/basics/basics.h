#pragma once

#include <string>
#include <vector>

namespace HW_05
{

class Point;

class IElement
{
public:
	virtual Point Get_Coordinate() = 0;
};

struct Point:
    public std::pair <int64_t, int64_t>,
    public IElement
{
    Point():
        std::pair <int64_t, int64_t>(0, 0)
    {}

    Point(int64_t x, int64_t y):
        std::pair <int64_t, int64_t>(x, y)
    {}

    Point Get_Coordinate() override
    {}
};

}
