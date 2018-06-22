#pragma once

#include "ifile.h"

namespace HW_05
{

namespace DATA_STORAGE
{

class cdr : public IFORMAT
{
public:
	std::string Import(std::string path);
	void Export(std::string path, std::string data);

private:
	std::string json_data;
};

}

}
