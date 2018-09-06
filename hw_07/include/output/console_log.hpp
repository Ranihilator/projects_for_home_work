/*!
\file
\brief console log header
*/
#pragma once

#include "log.hpp"

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
	Console(Observer *node):
		_node(node)
	{
		if (this->_node != nullptr)
			this->_node->subscribe(this);
	}

	~Console()
	{
		if (this->_node != nullptr)
			this->_node->unsubscribe(this);
	}

	void Act(std::ostringstream &ss)
	{
		std::cout << ss.str();
	}

private:
	Observer *_node;
};

}

}
