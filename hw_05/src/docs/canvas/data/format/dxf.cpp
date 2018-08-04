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
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Point()));
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Circle()));
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Line()));
}

void dxf::Export(SHAPES::Shapes *shape)
{
	if (!this->buffer.empty())
	{}
}

}

}
