#pragma once

#include "format/cdr.h"
#include "format/dxf.h"
#include "format/svg.h"
#include "format/vsd.h"

namespace HW_05
{

namespace DATA_STORAGE
{

/*!
\brief File controller
\details Save and load into file system
*/
class File
{
public:
	File(std::string path, SHAPES::Shapes *_shapes = nullptr);

	void Export(std::string &path);
	void Import(std::string &path);

private:
	void Load();

private:
	SHAPES::Shapes *shapes;

	std::unique_ptr<IFORMAT> format;
	std::fstream file_socket;
};

}

}
