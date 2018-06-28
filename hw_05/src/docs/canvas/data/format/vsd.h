#pragma once

#include "iformat.h"

namespace HW_05
{

namespace DATA_STORAGE
{

class vsd : public IFORMAT
{
public:
	vsd(std::fstream &_file);

	void Import(SHAPES::Shapes *shape);
	void Export(SHAPES::Shapes *shape);

private:
	std::fstream &file;
};

}

}
