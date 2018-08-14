#include "canvas.h"

namespace HW_05
{

namespace DOCUMENTS
{

Canvas::Canvas(std::string path):
	file(path, this)
{}

void Canvas::Export(std::string path)
{
	this->file.Export(path);
}

void Canvas::Import(std::string path)
{
	this->clear();
	this->file.Import(path);
}

}

}
