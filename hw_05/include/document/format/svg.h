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

	void write(Elements_Pool &elements)
	{
		for (auto i = 0; i < elements.size(); ++i)
			elements.get(i);
	}

	void read(Elements_Pool &elements)
	{
		elements.insert(new Point(0, 0));
	}
};

}
