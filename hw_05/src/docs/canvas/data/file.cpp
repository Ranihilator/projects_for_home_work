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

		this->file_socket.seekg(0, std::ios::end);
		auto length = this->file_socket.tellg();

		this->file_socket.seekg(0, std::ios::beg);

		this->buffer.clear();
		this->buffer.reserve(length);

		this->file_socket.read(reinterpret_cast<char*>(this->buffer.data()), this->buffer.capacity());

		this->file_socket.close();

		FORMATS formats = FORMATS::NUL;
		for (const auto &i : this->buffer)
		{
			//detect format = ...
		}

		return formats;
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

