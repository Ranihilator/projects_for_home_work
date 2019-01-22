/*!
\file
\brief console log header
*/
#pragma once

#include "log.h"

namespace HW_07
{

namespace LOG
{

/*!
\brief Console logger
*/
class Console:
	public Log
{
public:
	Console(Observer *node);
	~Console();

	void Act(std::ostringstream &ss);

private:
	Observer *_node;
};

}

}
