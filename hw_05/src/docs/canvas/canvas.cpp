#include "canvas.h"

namespace HW_05
{

namespace DOCUMENTS
{

Canvas::Canvas(std::string path):
	link(path, this)
{}

void Canvas::Export(std::string path)
{
	this->link.Export(path);
}

void Canvas::Import(std::string path)
{
	this->clear();
	this->link.Import(path);
}

}

}
