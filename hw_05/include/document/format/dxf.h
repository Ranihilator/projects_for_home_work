#pragma once

#include "file_extension.h"

namespace HW_05
{

class dxf : public IFormat
{
public:
	dxf()
	{}

	dxf(std::string path):
	    IFormat(path)
	{}

	void write()
	{}

	void read()
	{}
};

}
