#include "output/file_log.h"

namespace HW_07
{

namespace LOG
{

File::File(Observer *node):
	_node(node), time(0)
{
	if (this->_node != nullptr)
		this->_node->Subscribe(this);
}

File::~File()
{
	if (this->_node != nullptr)
		this->_node->Unsubscribe(this);
}

void File::Act(std::ostringstream &ss)
{
	if (time.count() == 0)
	{
		time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
		path = std::string("bulk") + std::to_string(time.count()) + std::string(".log");
	}

	std::ofstream fout(path, std::ofstream::app);
	fout << ss.str();
	fout.close();
}

std::string File::Get_file()
{
	return this->path;
}

}

}
