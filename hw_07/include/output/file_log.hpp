/*!
\file
\brief file log header
*/
#pragma once

#include "log.hpp"
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
	File(Observer *node):
		_node(node), time(0)
	{
		if (this->_node != nullptr)
			this->_node->subscribe(this);
	}

	~File()
	{
		if (this->_node != nullptr)
			this->_node->unsubscribe(this);
	}

	void Act(std::ostringstream &ss)
	{
		if (time.count() == 0)
			time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());

		std::ofstream fout(std::string("bulk") + std::to_string(time.count()) + std::string(".log"), std::ofstream::app);
		fout << ss.str();
		fout.close();
	}

private:
	Observer *_node;

	std::chrono::seconds time;
};

}

}
