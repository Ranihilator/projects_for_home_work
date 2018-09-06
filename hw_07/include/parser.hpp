/*!
\file
\brief bulk parser header
*/
#pragma once

#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include <ctime>

namespace HW_07
{

using Bulk_Function = std::function<size_t(void*)>;
using Bulk_Command = std::pair<const std::string, Bulk_Function>;

/*!
\brief Parser class
\details accept string and accumulate cmd sequency
*/
class Parser
{
protected:
	/*!
	\brief Parser constructor
	\param[in] _size sequence size
	*/
	Parser(size_t _size);

	/*!
	\brief Parser entry
	\param[in] _cmd input data
	\return result to act commands
	*/
	bool Act(std::string _cmd);

	std::vector<std::string> cmd_sequence;						///< sequence command list, ready to act

private:
	typename std::vector<std::string>::iterator pos;			///< current position, not ending sequence
	int32_t depth;												///< depth bracket sequence
	const size_t cmd_packets_size;								///< sequence size
};

}
