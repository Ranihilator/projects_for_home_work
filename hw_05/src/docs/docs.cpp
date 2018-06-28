#include "docs.h"

namespace HW_05
{

namespace DOCUMENTS
{

void Docs::insert(std::string name, std::string path)
{
	this->canvas[name] = Canvas(path);
}

void Docs::remove(std::string name)
{
	auto it = this->canvas.find(name);

	if (it != this->canvas.end())
		this->canvas.erase(it);
}

void Docs::Save(std::string name, std::string path)
{
	auto it = this->canvas.find(name);

	if (it != this->canvas.end())
		it->second.Export(path);
}

void Docs::Load(std::string name, std::string path)
{
	auto it = this->canvas.find(name);

	if (it != this->canvas.end())
		it->second.Import(path);
}

Canvas* Docs::find(std::string name)
{
	auto it = this->canvas.find(name);

	if (it != this->canvas.end())
		return &it->second;

	return nullptr;
}

}

}
