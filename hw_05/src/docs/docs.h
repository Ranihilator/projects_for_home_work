#pragma once

#include "canvas/canvas.h"

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
	void insert(std::string name, std::string path = std::string());
	void remove(std::string name);

	void Save(std::string name, std::string path);
	void Load(std::string name, std::string path);

	Canvas* find(std::string name);
private:
	std::map<std::string, Canvas> canvas;
};

}

}
