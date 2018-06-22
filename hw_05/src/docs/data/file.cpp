#include "file.h"

namespace HW_05
{

namespace DATA_STORAGE
{

File::File(IFORMAT *_format, std::string path):
	format(_format)
{
	this->file_socket.open(path, std::ifstream::binary);
}

char* File::Import()
{
	if (!this->file_socket)
		return nullptr;

	std::string buffer;
	this->file_socket >> buffer;

//	return this->format(buffer);
}

char* File::Export()
{
	if (!this->file_socket)
		return nullptr;
}

}

}
