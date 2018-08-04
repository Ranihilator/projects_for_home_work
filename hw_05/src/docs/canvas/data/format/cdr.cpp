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
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Point()));
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Circle()));
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Line()));
}

void cdr::Export(SHAPES::Shapes *shape)
{
	if (!this->buffer.empty())
	{}
}

}

}
