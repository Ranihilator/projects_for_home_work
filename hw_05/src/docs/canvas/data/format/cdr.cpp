#include "cdr.h"

namespace HW_05
{

namespace DATA_STORAGE
{

cdr::cdr(std::fstream &_file):
	file(_file)
{}

void cdr::Import(SHAPES::Shapes *shape)
{
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Point()));
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Circle()));
	shape->insert(std::unique_ptr<SHAPES::IShape>(new SHAPES::Line()));
}

void cdr::Export(SHAPES::Shapes *shape)
{
	if (this->file.is_open())
	{}
}

}

}
