/*!
\file
\brief file log header
*/
#pragma once

#include "log.h"
#include <fstream>
#include <chrono>


namespace HW_07
{

namespace LOG
{

/*!
\brief File logger
\details Created file log, and output data into file
*/
class File:
	public Log
{
public:
	File(Observer *node);
	~File();

	void Act(std::ostringstream &ss);
	std::string Get_file();

private:
	Observer *_node;

	std::chrono::seconds time;
	std::string path;
};

}

}
