#pragma once

#include "canvas.h"

namespace HW_05
{

namespace DOCUMENTS
{

/*!
\brief Docs creator
*/
class Docs
{
public:
	void insert(std::string name);

private:
	std::map<uint64_t, SHAPES::Shapes> docs;
};

}

}
