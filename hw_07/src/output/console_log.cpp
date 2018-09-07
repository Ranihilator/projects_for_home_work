#include "output/console_log.h"

namespace HW_07
{

namespace LOG
{

Console::Console(Observer *node):
	_node(node)
{
	if (this->_node != nullptr)
		this->_node->Subscribe(this);
}

Console::~Console()
{
	if (this->_node != nullptr)
		this->_node->Unsubscribe(this);
}

void Console::Act(std::ostringstream &ss)
{
	std::cout << ss.str();
}

}

}
