#pragma once

#include "file_extension.h"

namespace HW_05
{

class vsd : public IFormat
{
public:
	vsd()
	{}

	vsd(std::string path):
	    IFormat(path)
	{}

	void write()
	{}

	void read()
	{}
};

}
