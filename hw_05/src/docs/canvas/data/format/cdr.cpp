#include "cdr.h"

namespace HW_05
{

namespace DATA_STORAGE
{

cdr::cdr(std::vector<uint8_t> &_buffer):
	buffer(_buffer)
{}

void cdr::Import(SHAPES::Shapes *shape)
{
	shape->insert(new SHAPES::Point());
	shape->insert(new SHAPES::Circle());
	shape->insert(new SHAPES::Line());
}

void cdr::Export(SHAPES::Shapes *shape)
{
	if (!this->buffer.empty())
	{}
}

}

}
