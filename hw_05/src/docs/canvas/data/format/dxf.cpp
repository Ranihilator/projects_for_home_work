#include "dxf.h"

namespace HW_05
{

namespace DATA_STORAGE
{

dxf::dxf(std::vector<uint8_t> &_buffer):
	buffer(_buffer)
{}

void dxf::Import(SHAPES::Shapes *shape)
{
	shape->insert(new SHAPES::Point());
	shape->insert(new SHAPES::Circle());
	shape->insert(new SHAPES::Line());
}

void dxf::Export(SHAPES::Shapes *shape)
{
	if (!this->buffer.empty())
	{}
}

}

}
