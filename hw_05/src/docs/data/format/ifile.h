#pragma once

#include <string>

namespace HW_05
{

namespace DATA_STORAGE
{

class IFORMAT
{
public:
	virtual std::string Import(std::string path) = 0;
	virtual void Export(std::string path, std::string data) = 0;
};

}

}
