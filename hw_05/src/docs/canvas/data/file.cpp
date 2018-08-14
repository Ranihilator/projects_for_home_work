#include "file.h"

namespace HW_05
{

namespace DATA_STORAGE
{

File::File(std::string path, SHAPES::Shapes *_shapes):
	shapes(_shapes)
{
	this->file_socket.open(path, std::ifstream::binary);

	this->Load();
}

void File::Load()
{

	if (!this->file_socket.is_open())
		return;

	auto ident_format = [&]()
	{
		//parsing extension and format stamp in file's
		return FORMATS::NUL;
	};

	FORMATS formats = ident_format();

	switch (formats)
	{
		case FORMATS::CDR:
			this->format.reset(new cdr(this->file_socket));
			break;

		case FORMATS::DXF:
			this->format.reset(new dxf(this->file_socket));
			break;

		case FORMATS::SVG:
			this->format.reset(new svg(this->file_socket));
			break;

		case FORMATS::VSD:
			this->format.reset(new vsd(this->file_socket));
			break;
	}

	this->format->Import(this->shapes);
}

void File::Export(std::string &path)
{
	this->file_socket.open(path, std::ifstream::binary);

	this->format->Export(this->shapes);
}

void File::Import(std::string &path)
{
	this->file_socket.open(path, std::ifstream::binary);

	this->Load();
}

}

}
