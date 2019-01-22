#include "data_link.h"

namespace HW_05
{

namespace DATA_STORAGE
{

Data_Link::Data_Link(std::string path, SHAPES::Shapes *_shapes):
	socket(new File(path, _shapes))
{
}

Data_Link::Data_Link(std::string url_path, std::string name, std::string user, std::string password, SHAPES::Shapes *_shapes):
	socket(new DataBase(url_path, name, user, password, _shapes))
{
}

void Data_Link::Export(std::string &path)
{
///	this->format->Export(this->shapes);
}

void Data_Link::Import(std::string &path)
{
	//this->file_socket.open(path, std::ifstream::binary);
}

}

}
