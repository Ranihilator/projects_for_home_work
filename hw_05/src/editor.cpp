#include "editor.h"

namespace HW_05
{

void Editor::Create_Document(std::string name)
{
	this->insert(name);
}

void Editor::Close_Document(std::string name)
{
	this->remove(name);
}

void Editor::Save_Document(std::string name, std::string path)
{
	this->Save(name, path);
}

void Editor::Load_Document(std::string name, std::string path)
{
	this->Load(name, path);
}

void Editor::Select_Workspace(std::string name)
{
	this->Current_Workspace = this->find(name);
}

void Editor::Create_Shape(std::unique_ptr<SHAPES::IShape> _shape)
{
	if (this->Current_Workspace == nullptr)
		return;

	this->Current_Workspace->insert(std::move(_shape));
}

void Editor::Create_Shape(std::string name, std::unique_ptr<SHAPES::IShape> _shape)
{
	auto it = this->find(name);

	if (it == nullptr)
		return;

	it->insert(std::move(_shape));
}

void Editor::Delete_Shape(SHAPES::Coordinate_XY _coordinate)
{
	if (this->Current_Workspace == nullptr)
		return;

	this->Current_Workspace->remove(_coordinate);
}

void Editor::Delete_Shape(std::string name, SHAPES::Coordinate_XY _coordinate)
{
	auto it = this->find(name);

	if (it == nullptr)
		return;

	it->remove(_coordinate);
}

SHAPES::IShape* Editor::Select_Shape(SHAPES::Coordinate_XY _coordinate)
{
	if (this->Current_Workspace == nullptr)
		return nullptr;

	return this->Current_Workspace->find(_coordinate);
}

SHAPES::IShape* Editor::Select_Shape(std::string name, SHAPES::Coordinate_XY _coordinate)
{
	auto it = this->find(name);

	if (it == nullptr)
		return nullptr;

	return it->find(_coordinate);
}

}
