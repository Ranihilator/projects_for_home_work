/*!
\file
\brief bulk header
*/
#pragma once

#include "parser.hpp"
#include "output/console_log.hpp"
#include "output/file_log.hpp"

/*!
\brief HW_07 namespace
\details Bulk task
*/
namespace HW_07
{

/*!
\brief Bulk class
\details operate subscribe and unsubscribe procedure, call callback function at action commands
*/
class Bulk:
	private Parser, public LOG::Observer
{
public:
	/*!
	\brief Parser constructor
	\param[in] _size sequence size
	\param[in] aCommands sequence commands string and callback function
	*/
	Bulk(size_t _size = 3, std::initializer_list<Bulk_Command> aCommands = {});

	/*!
	\brief Bulk entry
	\details act callback, Subscriber service, and call parser
	\param[in] _cmd input data
	*/
	void Act(std::string _cmd);

protected:

	/*!
	\brief subscribe class
	\param[in] node client
	*/
	void subscribe(LOG::Log *node);

	/*!
	\brief unsubscribe class
	\param[in] node client
	*/
	void unsubscribe(LOG::Log *node);

private:
	std::unordered_set<LOG::Log *> _subscribe;							///< subscribe pool
	std::unordered_map<std::string, Bulk_Function> _commands;			///< registered commands
};

}
