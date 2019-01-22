#include "database.h"

namespace HW_05
{

namespace DATA_STORAGE
{

DataBase::DataBase(std::string path, std::string name, std::string user, std::string password, SHAPES::Shapes *_shapes):
	shapes(_shapes)
{
	this->db_socket;//.open(db_link, std::ifstream::binary);

	this->Load();
}

void DataBase::Load()
{
	//if (!this->db_socket.is_open())
		return;

	auto ident_format = [&]()
	{
		//parsing extension and format stamp in file's
		//this->db_socket.read(this->buffer);
		return FORMATS::NUL;
	};

	FORMATS formats = ident_format();

	switch (formats)
	{
		case FORMATS::CDR:
			this->format.reset(new cdr(this->buffer));
			break;

		case FORMATS::DXF:
			this->format.reset(new dxf(this->buffer));
			break;

		case FORMATS::SVG:
			this->format.reset(new svg(this->buffer));
			break;

		case FORMATS::VSD:
			this->format.reset(new vsd(this->buffer));
			break;
	}

	this->format->Import(this->shapes);
}

void DataBase::Export(std::string &path)
{
	this->db_socket;//.open(path, std::ifstream::binary);

	this->format->Export(this->shapes);
}

void DataBase::Import(std::string &path)
{
	this->db_socket;//.open(path, std::ifstream::binary);

	this->Load();
}

}

}

