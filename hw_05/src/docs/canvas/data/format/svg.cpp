#include "svg.h"

namespace HW_05
{

namespace DATA_STORAGE
{

svg::svg(std::vector<uint8_t> &_buffer):
	buffer(_buffer)
{}

void svg::Import(SHAPES::Shapes *shape)
{
	shape->insert(new SHAPES::Point());
	shape->insert(new SHAPES::Circle());
	shape->insert(new SHAPES::Line());
}

void svg::Export(SHAPES::Shapes *shape)
{
	if (!this->buffer.empty())
	{}
}

}

}
