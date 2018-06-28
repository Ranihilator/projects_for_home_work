#pragma once

#include "iformat.h"

namespace HW_05
{

namespace DATA_STORAGE
{

class cdr : public IFORMAT
{
public:
	cdr(std::fstream &_file);

	void Import(SHAPES::Shapes *shape);
	void Export(SHAPES::Shapes *shape);

private:
	std::fstream &file;
};

}

}
