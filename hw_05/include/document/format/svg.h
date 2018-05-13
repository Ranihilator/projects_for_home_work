#pragma once

#include "file_extension.h"

namespace HW_05
{

class svg : public IFormat
{
public:
	svg()
	{}

	svg(std::string path):
	    IFormat(path)
	{}

	void write()
	{}

	void read()
	{}
};

}
