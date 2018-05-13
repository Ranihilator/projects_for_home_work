#pragma once

#include "file_extension.h"

namespace HW_05
{

class cdr : public IFormat
{
public:
	cdr()
	{}

	cdr(std::string path):
	    IFormat(path)
	{}

	void write()
	{}

	void read()
	{}
};

}
