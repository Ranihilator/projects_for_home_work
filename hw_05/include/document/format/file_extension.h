#pragma once

#include <string>
#include <fstream>
#include "../elements/elements.h"

namespace HW_05
{

class IFormat
{
public:
    IFormat()
    {}

    IFormat(std::string &path):
        file(path)
    {}

	virtual void write() = 0;
	virtual void read() = 0;

protected:
    std::fstream file;
};

}

