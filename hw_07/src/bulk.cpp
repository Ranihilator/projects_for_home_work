#include "bulk.hpp"

namespace HW_07
{

Bulk::Bulk(size_t _size, std::initializer_list<Bulk_Command> aCommands):
	Parser(_size), _commands(aCommands)
{}

void Bulk::Act(std::string _cmd)
{
	std::ostringstream ss;
	if (this->Parser::Act(_cmd))
	{
		if (!this->cmd_sequence.empty())
			ss << "bulk: ";

		for (auto it = this->cmd_sequence.cbegin(); it != this->cmd_sequence.cend(); ++it)
		{
			auto cur_cmd = this->_commands.find(*it);
			if (cur_cmd != this->_commands.end())
				cur_cmd->second(&ss);
			else
				ss << *it;

			if (std::next(it) != this->cmd_sequence.cend())
				ss << ", ";
		}

		ss << std::endl;

		this->cmd_sequence.clear();
		for (const auto &i : this->_subscribe)
			i->Act(ss);
	}
}

void Bulk::subscribe(LOG::Log *node)
{
	if (node != nullptr)
		this->_subscribe.insert(node);
}

void Bulk::unsubscribe(LOG::Log *node)
{
	if (node == nullptr)
		return;

	auto it = this->_subscribe.find(node);
	if (it != this->_subscribe.end())
		this->_subscribe.erase(it);
}


}
