#include "parser.h"

namespace HW_07
{

Parser::Parser(size_t _size):
	cmd_packets_size(_size), depth(0), pos(cmd_sequence.begin())
{}

bool Parser::Act(const std::string &_cmd)
{
	if (_cmd.empty())
	{
		if (this->depth != 0)
			this->cmd_sequence.erase(this->pos, this->cmd_sequence.end());

		return true;
	}

	if (_cmd == "{")
	{
		if (this->depth == 0 && this->cmd_sequence.begin() != this->cmd_sequence.end())
			this->pos = std::prev(this->cmd_sequence.end());
		else
			this->pos = this->cmd_sequence.begin();

		this->depth++;
	}
	else
		if (_cmd == "}")
		{
			this->depth--;

			if (this->depth == 0)
				return true;
		}
		else
		{
			this->cmd_sequence.emplace_back(_cmd);

			if (this->cmd_sequence.size() >= this->cmd_packets_size && this->depth == 0)
				return true;
		}


	return false;
}

}
