#pragma once

#include "elements/elements.h"
#include "format/format.h"

namespace HW_05
{

class Document_Pool
{
public:
	Document_Pool()
	{}

	Document_Pool(IFormat *path):
		File(path)
	{
		this->File->read(this->elements);
	}

	void save(IFormat *path)
	{
		this->File->write(this->elements);
	}

	void Draw_Point(int64_t x, int64_t y)
	{
		this->elements.insert(new Point(x, y));
	}

	void Draw_Line(int64_t x1, int64_t y1, int64_t x2, int64_t y2)
	{
		this->elements.insert(new Line(Point(x1, y1), Point(x2, y2)));
	}

	void Draw_Square(int64_t x, int64_t y, int64_t s)
	{
		this->elements.insert(new Square(Point(x, y), s));
	}

	void Draw_Rectangle(int64_t dlc_x, int64_t dlc_y, int64_t urc_x, int64_t urc_y)
	{
		this->elements.insert(new Rectangle(Point(dlc_x, dlc_y), Point(urc_x, urc_y)));
	}

	void Draw_Circle(int64_t x, int64_t y, int64_t r)
	{
		this->elements.insert(new Circle(Point(x,y), r));
	}

	void Draw_Ellipse(int64_t l_x, int64_t l_y, int64_t r_x, int64_t r_y, int64_t u_x, int64_t u_y, int64_t d_x, int64_t d_y)
	{
		this->elements.insert(new Ellipse(Point(l_x, l_y), Point(r_x, r_y), Point(u_x, u_y), Point(d_x, d_y)));
	}

private:
	Elements_Pool elements;
	std::unique_ptr<IFormat> File;
};

}
