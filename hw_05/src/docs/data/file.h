#pragma once

#include "format/cdr.h"
#include "format/dxf.h"
#include "format/svg.h"
#include "format/vsd.h"

#include <fstream>

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
	File(IFORMAT *_format, std::string path);

	char* Import();
	char* Export();

private:
	IFORMAT *format;
	std::fstream file_socket;
};

/*!
\brief DB controller
\details Save and load into network
*/
class Network
{
public:

private:
};

}

}
