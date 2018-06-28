#pragma once

#include "docs/docs.h"

namespace HW_05
{

/*!
\brief Editor controller
*/
class Editor:
	private DOCUMENTS::Docs
{
public:
	void Create_Document(std::string name);
	void Close_Document(std::string name);

	void Save_Document(std::string name, std::string path);
	void Load_Document(std::string name, std::string path);

	void Select_Workspace(std::string name);

	void Create_Shape(std::unique_ptr<SHAPES::IShape> _shape);
	void Create_Shape(std::string name, std::unique_ptr<SHAPES::IShape> _shape);

	void Delete_Shape(SHAPES::Coordinate_XY _coordinate);
	void Delete_Shape(std::string name, SHAPES::Coordinate_XY _coordinate);

	SHAPES::IShape* Select_Shape(SHAPES::Coordinate_XY _coordinate);
	SHAPES::IShape* Select_Shape(std::string name, SHAPES::Coordinate_XY _coordinate);

private:
	DOCUMENTS::Canvas* Current_Workspace = nullptr;
};

}
