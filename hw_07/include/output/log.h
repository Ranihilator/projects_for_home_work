/*!
\file
\brief file log header
*/
#pragma once

#include <iostream>
#include <sstream>

namespace HW_07
{

/*!
\brief LOG namespace
\details Logger subscribes
*/
namespace LOG
{

class File;
class Console;

/*!
\brief Log interface
\details subscribers logger
*/
class Log
{
public:
	virtual void Act(std::ostringstream &ss) = 0;
};


/*!
\brief Observer interface
\details for HW_07::Bulk class
*/
class Observer
{
friend Console;
friend File;

protected:
	virtual void Subscribe(LOG::Log *node) = 0;
	virtual void Unsubscribe(LOG::Log *node) = 0;

};

}

}
