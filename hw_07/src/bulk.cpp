#include "bulk.h"

#include <assert.h>

namespace HW_07
{

Bulk::Bulk(size_t _size, std::initializer_list<Bulk_Command> aCommands):
	Parser(_size), commands(aCommands)
{}

void Bulk::Act(const std::string &_cmd)
{
	std::ostringstream ss;
	if (this->Parser::Act(_cmd))
	{
		if (!this->cmd_sequence.empty())
			ss << "bulk: ";

		for (auto it = this->cmd_sequence.cbegin(); it != this->cmd_sequence.cend(); ++it)
		{
			auto cur_cmd = this->commands.find(*it);
			if (cur_cmd != this->commands.end())
				cur_cmd->second(&ss);
			else
				ss << *it;

			if (std::next(it) != this->cmd_sequence.cend())
				ss << ", ";
		}

		if (!this->cmd_sequence.empty())
			ss << std::endl;

		this->cmd_sequence.clear();
		for (const auto &i : this->subscribe)
			i->Act(ss);
	}
}

void Bulk::Subscribe(LOG::Log *node)
{
	#ifndef NDEBUG
	assert(node != nullptr);
	#endif

	if (node != nullptr)
		this->subscribe.insert(node);
}

void Bulk::Unsubscribe(LOG::Log *node)
{
	#ifndef NDEBUG
	assert(node != nullptr);
	#endif

	if (node == nullptr)
		return;

	auto it = this->subscribe.find(node);
	if (it != this->subscribe.end())
		this->subscribe.erase(it);
}


}
